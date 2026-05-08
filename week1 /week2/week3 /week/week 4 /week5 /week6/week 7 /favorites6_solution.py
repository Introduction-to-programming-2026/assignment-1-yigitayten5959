import csv
from collections import Counter

# We use 'with' to ensure the file closes automatically
with open("../week1/favorites.csv", "r") as file:
    reader = csv.DictReader(file)
    
    # Counter automatically handles the "if key exists" logic for us
    counts = Counter()

    for row in reader:
        counts[row["language"]] += 1

# Print the results sorted by most popular
for language, count in counts.most_common():
    print(f"{language}: {count}")
