s = input("Do you agree?\n")

#if s == "Y" or s == "y":
if s.lower() in ["yes", "y"]:
    print("Agreed.")

#elif s == "N" or s == "n":
elif s.lower() in ["no", "n", "nope"]:
    print("Not agreed.")