from cs50 import SQL

# Connect to the SQLite database
db = SQL("sqlite:///favorites.db")

# 1. Execute the SQL query
# This one line of SQL replaces the dictionaries, if/else blocks, and sorting loops
rows = db.execute(
    "SELECT language, COUNT(*) AS n FROM favorites GROUP BY language ORDER BY n DESC"
)

# 2. Iterate through the results
# db.execute returns a list of dictionaries, where each dictionary is a row
for row in rows:
    print(f"{row['language']} {row['n']}")
