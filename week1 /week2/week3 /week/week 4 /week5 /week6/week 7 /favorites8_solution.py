import csv

# Open the CSV data file for reading
with open("../week1/favorites.csv", "r") as file:
    reader = csv.DictReader(file)
    
    # Use a descriptive dictionary name
    language_counts = {}

    for row in reader:
        favorite_language = row["language"]
        
        # If the language exists, increment the count; otherwise, initialize it
        if favorite_language in language_counts:
            language_counts[favorite_language] += 1
        else:
            language_counts[favorite_language] = 1

# Sort the dictionary by values (counts) in descending order (highest first)
for language in sorted(language_counts, key=language_counts.get, reverse=True):
    print(f"{language}: {language_counts[language]}")
