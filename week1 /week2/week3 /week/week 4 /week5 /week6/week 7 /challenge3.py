import csv

# Input and output filenames
input_file = "favorites.csv"
output_file = "language_summary.csv"

counts = {}

try:
    # 1. Read the data from the source file
    with open(input_file, "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            lang = row["language"]
            if lang in counts:
                counts[lang] += 1
            else:
                counts[lang] = 1

    # 2. Write the results to a new summary file
    with open(output_file, "w", newline="") as file:
        # Create a writer object
        writer = csv.writer(file)
        
        # Write the header row
        writer.writerow(["Language", "Votes"])
        
        # Write the data rows (sorted by language name)
        for lang in sorted(counts):
            writer.writerow([lang, counts[lang]])

    print(f"Successfully created {output_file} with {len(counts)} languages.")

except FileNotFoundError:
    print(f"Error: {input_file} not found.")
