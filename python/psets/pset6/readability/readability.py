# Get text to evaluate
text = input("Text: ")

# Get length of inputted text
text_len = len(text)

# Set up counter variables.  Words starting at 1 because of last word not having space after it.
num_letters = 0
num_words = 1
num_sentences = 0

# Loop through each character in text
for i in text:

    # If the current character is a space, increment the num_words counter
    if i == " ":
        num_words += 1

    #If the current character is punctuation, increment the num_sentances counter
    elif i == "." or i == "!" or i == "?":
        num_sentences += 1

    # Otherwise, increment num_chars counter because it is a regular letter
    else:
        num_letters +=1

#Calculate reading level using Coleman-Liau index
L = 100 * float(num_letters) / float(num_words)
S = 100 * float(num_sentences) / float(num_words)
index = 0.0588 * L - 0.296 * S - 15.8
rounded_index = int(index)

#Print results
if rounded_index < 1:
    print("Before Grade 1")

elif rounded_index >= 16:
    print("Grade 16+")

else:
    print(f"Grade {rounded_index}")