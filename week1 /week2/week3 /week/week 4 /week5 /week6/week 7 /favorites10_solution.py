# favorites10_solution.py
from cs50 import SQL

# Connect to the SQLite database
# The prefix "sqlite:///" tells the library where the file is located
db = SQL("sqlite:///favorites.db")

# Prompt the user for an input (e.g., "Pointers", "Loops", "Functions")
favorite = input("Favorite problem: ")

# Execute a SQL query to count occurrences
# The "?" is a placeholder to prevent SQL Injection (security best practice)
# We name the result "n" using 'AS n' for easier access
rows = db.execute(
    "SELECT COUNT(*) AS n FROM favorites WHERE problem = ?", favorite
)

# db.execute returns a LIST of dictionaries: [{'n': 42}]
# We take the first (and only) dictionary in that list
row = rows[0]

# Print the value associated with the key "n"
print(f"Total votes for '{favorite}': {row['n']}")
