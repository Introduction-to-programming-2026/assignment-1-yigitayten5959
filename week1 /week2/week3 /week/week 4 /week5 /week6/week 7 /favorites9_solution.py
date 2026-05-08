from cs50 import SQL

# Connect to the SQLite database file
db = SQL("sqlite:///favorites.db")

# Execute a query to count languages directly in the database
# English translation of the SQL: 
# "Find each language, count how many times it appears, 
# group them by name, and sort by the count from highest to lowest."
rows = db.execute(
    "SELECT language, COUNT(*) AS count FROM favorites GROUP BY language ORDER BY count DESC"
)

# Print each row found in the database results
for row in rows:
    print(f"{row['language']}: {row['count']}")
