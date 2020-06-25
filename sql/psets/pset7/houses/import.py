import cs50
import sys
import csv

### Exit and print usage if not all arguments are provided (or too many are provided)
if len(sys.argv) != 2:
    print("Usage: python import.py data.csv")
    exit(1)
    
### CSV file is provided - open file and create CSV reader for it
else:
    csv_file = open(sys.argv[1], "r")
    csv_reader = csv.DictReader(csv_file)

### Open the students DB
db = cs50.SQL("sqlite:///students.db")

### Loop through each student record in the CSV file
for row in csv_reader:

    ### Pull fields from CSV file for insertion into DB
    birth = row["birth"]
    house = row["house"]

    ### Name field may contain middle name, split into list for parsing
    name = row["name"].split()
    
    ### If the name only has a length of 2, set first and last names, but set middle name to NULL
    if len(name) == 2:
        first = name[0]
        middle = None
        last = name[1]

    ### If the name has a length of 3, set first, middle, and last names
    elif len(name) == 3:
        first = name[0]
        middle = name[1]
        last = name[2]

    ### Insert fields extracted from CSV into the DB
    db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?,?,?,?,?)", first, middle, last, house, birth)

### Close the CSV file and exit
csv_file.close()
exit(1)