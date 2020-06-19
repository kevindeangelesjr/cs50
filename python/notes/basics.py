# Print text
print("hello, world")

# Get input and print (3 different approaches to concatenation)
#answer = get_string("What's your name?\n")
answer = "Kevin"
print("hello, " + answer)
print("hello, ", answer)
print(f"hello, {answer}") # f-string

# Assign variable
counter = 0
counter += 1

# If statements
x = 1
y = 2
if x < y:
    print("x is less than y")
elif x > y:
    print("x is greater than y")
else:
    print("x is equal to y")

# While loop
while True:
    print("hello world")

i = 3
while i > 0:
    print("cough")
    i -=1

# for loop
for i in [0, 1, 2]:
    print("cough")

for i in range(3):
    print("cough")

# data types
# range - sequence of numbers
# list - sequence of mutable values (array)
# tuple - sequence of immutable values
# dict - collection of key/value pairs (hash table)
# set - collection of unique values (throws away duplicates)