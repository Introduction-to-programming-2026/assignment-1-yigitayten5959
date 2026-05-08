import csv

# Open the CSV file for reading
# Ensure favorites.csv is in the same directory as this script
try:
    with open("favorites.csv", "r") as file:
        # Create a DictReader to use the header row as keys
        reader = csv.DictReader(file)
        
        counts = {}

        # Iterate over the file and count occurrences of each title
        # (Assuming the column header is 'title')
        for row in reader:
            title = row["title"]
            if title in counts:
                counts[title] += 1
            else:
                counts[title] = 1

    # Ask the user for a minimum frequency filter
    minimum = int(input("Minimum vote count: "))

    # Sort and print filtered results
    print("\n--- Filtered Results ---")
    found = False
    for title in sorted(counts):
        if counts[title] >= minimum:
            print(f"{title}: {counts[title]}")
            found = True

    if not found:
        print("No items met that threshold.")

except FileNotFoundError:
    print("Error: favorites.csv not found.")
