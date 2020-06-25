import cs50
import sys

### Exit and print usage if not all arguments are provided (or too many are provided)
if len(sys.argv) != 2:
    print("Usage: python roster.py house")
    exit(1)

### If provided properly, convert house to title case for querying sake
else:
    house = sys.argv[1].title()

### Open the students DB
db = cs50.SQL("sqlite:///students.db")

### Query the DB for names and birth for records where the house matches the provided house
query_results=db.execute("SELECT first,middle,last,birth FROM students WHERE house=(?) ORDER BY last", house)

### Loop through queries returned
for result in query_results:

    ### Set values with values from query result
    birth = result['birth']
    first = result['first']
    middle = result['middle']
    last = result['last']

    ### If no middle name
    if middle == None:
        print(f"{first} {last}, born {birth}")
    
    ### If middle name
    else:
        print(f"{first} {middle} {last}, born {birth}")
    
exit(0)