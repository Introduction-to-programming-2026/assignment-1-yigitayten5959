# favorites3.py
# Task: Print directly from the dictionary for a more concise script.

import csv

with open("favorites.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        # Access and print in a single step
        print(row["language"]
