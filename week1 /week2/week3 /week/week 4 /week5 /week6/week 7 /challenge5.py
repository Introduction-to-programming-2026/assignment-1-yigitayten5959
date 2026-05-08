# challenge5.py — Data Cleaner
# Author: Gemini

import csv

# Files
INPUT_FILE = "messy_data.csv"
OUTPUT_FILE = "cleaned_data.csv"

def clean_data():
    # Tracking stats for the report
    stats = {
        "total_rows": 0,
        "cleaned_rows": 0,
        "missing_values_fixed": 0,
        "case_errors_fixed": 0
    }

    try:
        with open(INPUT_FILE, "r") as infile, open(OUTPUT_FILE, "w", newline="") as outfile:
            reader = csv.DictReader(infile)
            # Use the same fieldnames for the output file
            writer = csv.DictWriter(outfile, fieldnames=reader.fieldnames)
            writer.writeheader()

            for row in reader:
                stats["total_rows"] += 1
                is_cleaned = False

                # 1. Handle Case Sensitivity (e.g., "python" vs "Python")
                if row["language"] != row["language"].capitalize():
                    row["language"] = row["language"].capitalize()
                    stats["case_errors_fixed"] += 1
                    is_cleaned = True

                # 2. Handle Missing Values
                # If a field is empty, provide a default value
                for key, value in row.items():
                    if not value or value.strip() == "":
                        row[key] = "Unknown"
                        stats["missing_values_fixed"] += 1
                        is_cleaned = True

                # 3. Clean whitespace
                for key in row:
                    row[key] = row[key].strip()

                if is_cleaned:
                    stats["cleaned_rows"] += 1

                writer.writerow(row)

        # Print the Cleaning Report
        print("\n--- Data Cleaning Report ---")
        print(f"Total rows processed: {stats['total_rows']}")
        print(f"Rows requiring cleaning: {stats['cleaned_rows']}")
        print(f"Missing values filled: {stats['missing_values_fixed']}")
        print(f"Capitalization errors fixed: {stats['case_errors_fixed']}")
        print(f"\nSuccess! Cleaned data saved to: {OUTPUT_FILE}")

    except FileNotFoundError:
        print(f"Error: {INPUT_FILE} not found. Please create it first.")

if __name__ == "__main__":
    clean_data()
