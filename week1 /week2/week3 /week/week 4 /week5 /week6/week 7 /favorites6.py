import csv

# Open the file and use a dictionary to track totals
with open("../week1/favorites.csv", "r") as file:
    reader = csv.DictReader(file)
    language_counts = {}

    for row in reader:
        favorite_language = row["language"]

        # EAFP Style: Try the operation first
        try:
            # If the language is already in the dictionary, this works
            language_counts[favorite_language] += 1
        except KeyError:
            # If the language is NOT there, a KeyError occurs
            # We "catch" it and initialize the count to 1
            language_counts[favorite_language] = 1

# Print each language and its final total
for language in language_counts:
    print(f"{language}: {language_counts[language]}")
