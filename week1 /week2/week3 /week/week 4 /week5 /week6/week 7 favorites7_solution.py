import csv

# We use 'with' to ensure the file is closed automatically after reading
with open("../week1/favorites.csv", "r") as file:
    reader = csv.DictReader(file)
    
    # Using a descriptive name like 'language_counts' instead of just 'counts'
    language_counts = {}

    for row in reader:
        favorite_language = row["language"]
        
        # Check if the language is already a key in our dictionary
        if favorite_language in language_counts:
            language_counts[favorite_language] += 1
        else:
            # If it's the first time seeing this language, initialize it to 1
            language_counts[favorite_language] = 1

# 'sorted()' sorts the keys of the dictionary alphabetically (A-Z)
for language in sorted(language_counts):
    print(f"{language}: {language_counts[language]}")
