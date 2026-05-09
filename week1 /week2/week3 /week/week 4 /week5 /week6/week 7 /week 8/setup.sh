#!/bin/bash
# setup.sh — Initialize all practice databases for Week 8 SQL exercises
# Usage: bash setup.sh

# Exit immediately if a command exits with a non-zero status
set -e

echo "🗄️  Week 8 SQL — Database Setup"
echo "================================"

# Check for sqlite3 installation
if ! command -v sqlite3 &>/dev/null; then
    echo "❌ sqlite3 not found."
    echo "    Please install it to continue:"
    echo "    • Ubuntu/Debian: sudo apt install sqlite3"
    echo "    • macOS:         brew install sqlite"
    echo "    • Windows:       https://www.sqlite.org/download.html"
    exit 1
fi

echo "✅ sqlite3 found: $(sqlite3 --version)"

# Create the data directory if it doesn't exist
mkdir -p data

# Remove old databases if they exist to ensure a fresh start
rm -f data/school.db data/library.db

# Build databases from SQL source files
echo ""
echo "📦 Creating school.db..."
sqlite3 data/school.db < data/school.sql
echo "    ✅ school.db created"
echo "      Tables: $(sqlite3 data/school.db '.tables')"

echo ""
echo "📦 Creating library.db..."
sqlite3 data/library.db < data/library.sql
echo "    ✅ library.db created"
echo "      Tables: $(sqlite3 data/library.db '.tables')"

echo ""
echo "🎉 Setup complete! You're ready to start."
echo ""
echo "Quick start:"
echo "  sqlite3 data/school.db"
echo "  sqlite> .headers on"
echo "  sqlite> .mode column"
echo "  sqlite> SELECT * FROM students LIMIT 5;"
echo ""
echo "Exercise Path Index:"
echo "  01-Basics      → exercises/01-basics/"
echo "  02-Queries     → exercises/02-queries/"
echo "  03-Joins       → exercises/03-joins/"
echo "  04-Aggregates  → exercises/04-aggregates/"
echo "  05-Subqueries  → exercises/05-subqueries/"
echo "  06-Design      → exercises/06-design/"
echo "  07-Advanced    → exercises/07-advanced/"
echo ""
echo "Happy coding! 🚀"
