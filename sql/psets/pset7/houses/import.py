import cs50
import sys
import csv

### Exit and print usage if not all arguments are provided (or too many are provided)
if len(sys.argv) != 2:
    print("Usage: python import.py data.csv")