# favorites4.py
# Task: Count language choices using separate variables.

import csv

with open("favorites.csv", "r") as file:
    reader = csv.DictReader(file)

    # Initialize counter variables at zero
    scratch = 0
    c = 0
    python = 0

    for row in reader:
        favorite = row["language"]
        
        # Increment the corresponding counter
        if favorite == "Scratch":
            scratch += 1
        elif favorite == "C":
            c += 1
        elif favorite == "Python":
            python += 1

    # Print the final results
    print(f"Scratch: {scratch}")
    print(f"C: {c}")
    print(f"Python: {python}")
