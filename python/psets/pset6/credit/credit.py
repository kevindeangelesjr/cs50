import re

# Get credit card number as input
card_num = input("Number: ")
num_len = len(card_num)
even_sum = 0
odd_sum = 0
position = num_len - 1

# Iterate through each number of the card
for num in card_num:

    # position starts from last number of card
    # if the current position is odd, double it
    if position % 2 != 0:
        doubled_num = int(num) * 2

        # Add each digit of the product to the odd_sum
        for i in str(doubled_num):
            odd_sum += int(i)
    
    # If the current position is even, add the number to the even_sum
    else:
        even_sum += int(num)
    
    position += 1

# Calculate checksum
checksum = even_sum + odd_sum

# Last digit of check sum has to be 0 (% of 0)
if checksum % 10 == 0:
    
    # Passes checksum

    if (num_len == 15 and card_num[0] == "3") and re.search("4|7", card_num[1]):
        print("AMEX")
    elif (num_len == 16 and card_num[0] == "5") and re.search("1|2|3|4|5", card_num[1]):
        print("MASTERCARD")
    elif (num_len == 13 and card_num[0] == "4") or (num_len == 16 and card_num[0] == "4"):
        print("VISA")
    else:
        print("INVALID")

# Fails checksum
else:
    print("INVALID")

