height = 0

while height <= 0 or height > 8:
    height = int(input("Height: "))

for i in range(height):
    print(" " * (height-i-1), end="")
    print("#" * (i+1), end="")
    print(" " * 2, end="")
    print("#" * (i+1), end="")
    print()