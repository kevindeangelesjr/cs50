import sys
import csv

### Exit and print usage if not all arguments are provided (or too many are provided)
if len(sys.argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
else:
    database = sys.argv[1]
    sequence = sys.argv[2]

### Open sequence file (txt)
sequence_file = open(sequence, "r")
sequence_list = []
### Convert sequence file to list in memory
for char in sequence_file.read():
    sequence_list.append(char)
### Remove newline character if it exists in the list
if "\n" in sequence_list:
    sequence_list.remove("\n")
### Close sequence file
sequence_file.close()

### Open database file and then open with a CSV reader from the csv module
database_file = open(database, "r")
reader = csv.reader(database_file)
### Create list with STRs to check, pulled from CSV database headers
str_list = next(reader, None)
del str_list[0] # First field is name, we don't want that
### Close database CSV file
database_file.close()

### Create dictionary str_count with STRs as keys, intialize with value of 0 for each
str_count = {}
for str_sequence in str_list:
    str_count.update( {str_sequence : 0} )

### Loop through sequence file looking for each STR
for str_sequence in str_list:
    str_len = len(str_sequence)

    ### Counter for keeping track of the current position on the list
    pos_counter = 0
    ### Counters for keeping track of current length of STR sequence, as well as the largest found so far
    max_sequence_count = 0
    new_sequence_count = 0
    ### Becomes True if we find the STR in the DNA sequence
    prev_match = False

    ### Loop through each sequence in the list of STRs that we are looking for
    for char in sequence_list:

        ### Take a slice of the DNA sequence that goes from the current position to the current position + the length of the current STR we are looking for
        if ''.join(sequence_list[pos_counter:pos_counter+str_len]) == str_sequence:
            ### If the slice matches the STR we are looking for, set prev_match to True, which will activate the below while loop
            prev_match = True
            
            ### Moves through the DNA list in increments of the length of the STR (str_len) looking for more consecutive matches of the STR
            while prev_match:
                ### If we find another match to the STR consecutively
                if ''.join(sequence_list[pos_counter:pos_counter+str_len]) == str_sequence:
                    new_sequence_count +=1
                    pos_counter += str_len
                ### If we do not find another consecutive match to the STR, break out of the loop
                else:
                    prev_match = False

            ### If the new_sequence_count from the previous run of the above while loop is the largest
            if new_sequence_count > max_sequence_count:
                max_sequence_count = new_sequence_count

            new_sequence_count = 0

        pos_counter += 1

    ### Update str_count dictionary with the max sequence count of each STR
    str_count.update( {str_sequence : max_sequence_count} )

### Open database file again, this time with CSV DictReader - turns each line into a dictionary
database_file = open(database, "r")
reader = csv.DictReader(database_file)

### Compare STR counts against CSV database file to find a match
### Loop through each line of the CSV database file
for row in reader:
    match = True

    ### Loop through DNA sequence
    for sequence in str_list:
        ### match is set to true before this loop, so if the STR count for this row matches the STR count in the str_count dictionary, simply continue
        if int(row[sequence]) == int(str_count[sequence]):
            continue
        ### Set match to false if the STR count for this row DOES NOT match the STR count in the str_count dictionary
        else:
            match = False

    ### Print the match name and exit if match is still true (all STR counts from provided sequence match counts in the database)
    if match:
        print(row['name'])
        database_file.close()
        sys.exit(0)

    ### Else continue onto the next row (person) in the database
    else:
        continue

### Print no match if no match is found in the database
print("No match")
database_file.close()
sys.exit(1)