# favorites5.py
# Task: Count languages using a dynamic dictionary.

import csv

with open("favorites.csv", "r") as file:
    reader = csv.DictReader(file)

    # Dictionary to store language as the Key and count as the Value
    counts = {}

    for row in reader:
        favorite = row["language"]
        
        # Check if the language is already a key in our dictionary
        if favorite in counts:
            counts[favorite] += 1
        else:
            # If it's a new language, initialize it at 1
            counts[favorite] = 1

    # Print each language and its final tally
    for language in counts:
        print(f"{language}: {counts[language]}") 
