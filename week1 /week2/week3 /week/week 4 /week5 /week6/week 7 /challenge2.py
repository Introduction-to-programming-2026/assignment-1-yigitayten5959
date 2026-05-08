import csv

# Path to the data file
filename = "favorites.csv"

# Nested dictionary: { language: { problem: count } }
data = {}

try:
    with open(filename, "r") as file:
        reader = csv.DictReader(file)
        
        for row in reader:
            lang = row["language"]
            prob = row["problem"]
            
            # If the language isn't in our data yet, add it
            if lang not in data:
                data[lang] = {}
            
            # If the problem isn't in that language's dict, start at 1, else increment
            if prob not in data[lang]:
                data[lang][prob] = 1
            else:
                data[lang][prob] += 1

    # Print Header
    print(f"\n{'Language':<15} | {'Most Common Problem':<25} | {'Count'}")
    print("-" * 55)

    # Analyze and print results
    for lang in sorted(data):
        # Find the problem with the maximum value in the nested dictionary
        # The key=data[lang].get part tells max() to compare the counts (values)
        most_common_prob = max(data[lang], key=data[lang].get)
        count = data[lang][most_common_prob]
        
        print(f"{lang:<15} | {most_common_prob:<25} | {count}")

except FileNotFoundError:
    print(f"Error: {filename} not found.")
