# favorites1.py
# Task: Store the language in a variable called 'favorite' before printing it.

import csv

# Open the CSV file for reading
with open("favorites.csv", "r") as file:
    # Create a CSV reader object
    reader = csv.reader(file)
    
    # Skip the header row (Timestamp, Language, etc.)
    next(reader)
    
    # Iterate through each row in the file
    for row in reader:
        # Store the second column (index 1) in a descriptive variable
        favorite = row[1]
        
        # Print the stored value
        print(favorite)
