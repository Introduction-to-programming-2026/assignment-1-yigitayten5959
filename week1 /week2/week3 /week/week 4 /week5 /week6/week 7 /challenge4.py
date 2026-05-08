# challenge4.py — SQL Explorer
# Author: Gemini

import sqlite3

def main():
    # Connect to the SQLite database
    try:
        # Connect to the database file
        connection = sqlite3.connect("favorites.db")
        # The cursor allows us to execute SQL commands
        db = connection.cursor()
    except sqlite3.Error:
        print("Error: Could not find or open favorites.db.")
        return

    while True:
        # Display the Menu
        print("\n--- SQL Explorer Menu ---")
        print("1. Show all unique languages")
        print("2. Count votes for a specific language")
        print("3. Find the most common problem for a language")
        print("4. Search for a keyword in problems")
        print("5. Exit")

        choice = input("\nSelect an option (1-5): ")

        if choice == "1":
            # Execute a SELECT DISTINCT query
            rows = db.execute("SELECT DISTINCT(language) FROM favorites ORDER BY language")
            print("\nLanguages in database:")
            for row in rows:
                print(f"- {row[0]}")

        elif choice == "2":
            lang = input("Enter language: ")
            # Use placeholders (?) to prevent SQL Injection attacks
            rows = db.execute("SELECT COUNT(*) FROM favorites WHERE language = ?", (lang,))
            count = rows.fetchone()[0]
            print(f"\n{lang} has {count} total votes.")

        elif choice == "3":
            lang = input("Enter language: ")
            query = """
                SELECT problem, COUNT(*) AS n 
                FROM favorites 
                WHERE language = ? 
                GROUP BY problem 
                ORDER BY n DESC 
                LIMIT 1
            """
            rows = db.execute(query, (lang,))
            result = rows.fetchone()
            if result:
                print(f"\nMost common problem for {lang}: {result[0]} ({result[1]} votes)")
            else:
                print(f"\nNo data found for {lang}.")

        elif choice == "4":
            keyword = input("Enter keyword to search for: ")
            # Use LIKE for partial matches (e.g., %pointer%)
            rows = db.execute("SELECT language, problem FROM favorites WHERE problem LIKE ?", (f"%{keyword}%",))
            print(f"\nResults for '{keyword}':")
            for row in rows:
                print(f"[{row[0]}] {row[1]}")

        elif choice == "5":
            print("Goodbye!")
            break
        else:
            print("Invalid choice, please try again.")

    # Close the database connection
    connection.close()

if __name__ == "__main__":
    main()
