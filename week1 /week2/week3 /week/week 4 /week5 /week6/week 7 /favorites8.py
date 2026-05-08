import csv

# Open the file and count language occurrences
with open("../week1/favorites.csv", "r") as file:
    reader = csv.DictReader(file)
    language_counts = {}

    for row in reader:
        favorite_language = row["language"]
        if favorite_language in language_counts:
            language_counts[favorite_language] += 1
        else:
            language_counts[favorite_language] = 1

# Sorting by popularity (highest count first)
# 'key=language_counts.get' tells sorted() to look at the numbers, not the names
# 'reverse=True' flips the order from ascending to descending
for language in sorted(language_counts, key=language_counts.get, reverse=True):
    print(f"{language}: {language_counts[language]}")
