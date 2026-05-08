# favorites0_solution.py
import csv

# Open the CSV file in read mode
with open("favorites.csv", "r") as file:
    # Create a reader object to iterate over lines in the CSV
    reader = csv.reader(file)
    
    # Skip the header row (the first line with column names)
    next(reader)
    
    # Iterate through the remaining rows
    for row in reader:
        # Print the second column (index 1) of each row
        # In the CS50 dataset, this is usually the 'language' or 'title'
        print(row[1])
