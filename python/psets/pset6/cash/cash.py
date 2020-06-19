owed = -1

while owed < 0:
    owed = float(input("How much change is owed?\n"))

dollars = int(owed / 1)
cents = int(round((owed % 1), 2) * 100)
coin_counter = 0

while dollars > 0:
    coin_counter +=4
    dollars -=1

while cents > 0:
    if cents >= 25:
        cents -= 25
        coin_counter += 1

    elif cents >= 10:
        cents -= 10
        coin_counter += 1

    elif cents >= 5:
        cents -= 5
        coin_counter += 1

    elif cents >= 1:
        cents -= 1
        coin_counter += 1

print(coin_counter)