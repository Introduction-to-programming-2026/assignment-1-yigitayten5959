# favorites5_solution.py
import csv

# Open the CSV file for reading
with open("favorites.csv", "r") as file:
    # Use DictReader to treat the first row as headers
    # This allows us to access data by column name instead of index
    reader = csv.DictReader(file)
    
    # Initialize an empty dictionary to store our tallies
    counts = {}
    
    # Iterate through every row in the spreadsheet
    for row in reader:
        # Extract the value from the "language" column
        favorite = row["language"]
        
        # If the language is already in our dictionary, increment the count
        if favorite in counts:
            counts[favorite] += 1
        # Otherwise, add the language to the dictionary with an initial count of 1
        else:
            counts[favorite] = 1

# Print the results to the terminal
# This loop goes through every key (language) we found
for favorite in counts:
    print(f"{favorite}: {counts[favorite]}")
