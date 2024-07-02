from cs50 import get_string


def main():
    # Prompt the user for some text
    text = get_string("Text: ")

    # Count the number of letter, words and sentences in the text
    cL = count_letters(text)
    cW = count_words(text)
    cS = count_sentences(text)

    # Coleman-Liau Index Formula
    L = (cL / cW) * 100
    S = (cS / cW) * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # Print the grade level
    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")


def count_letters(text):
    # Return number of letters in text
    letters = 0
    for i in text:
        if str.isalpha(i):
            letters += 1
    return letters


def count_words(text):
    # Return number of words in text
    words = 1
    for i in text:
        if str.isspace(i):
            words += 1
    return words


def count_sentences(text):
    # Return number of sentences in texts
    sentences = 0
    for i in text:
        if i == '.' or i == '!' or i == '?':
            sentences += 1
    return sentences


main()
