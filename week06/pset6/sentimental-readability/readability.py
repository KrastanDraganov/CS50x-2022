from cs50 import get_string


def main():
    text = get_string("Text: ")

    letter_count = count_letters(text)
    word_count = count_words(text)
    sentence_count = count_sentences(text)

    L = 100 * letter_count / word_count
    S = 100 * sentence_count / word_count

    index = 0.0588 * L - 0.296 * S - 15.8
    grade = round(index)

    if grade >= 16:
        print("Grade 16+")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {grade}")


def count_letters(text):
    counter = 0

    for c in text:
        if c.isalpha():
            counter += 1

    return counter


def count_words(text):
    counter = 0

    for c in text:
        if c.isspace():
            counter += 1

    # count last word in the text
    counter += 1

    return counter


def count_sentences(text):
    counter = 0

    for c in text:
        if c in ['.', '!', '?']:
            counter += 1

    return counter


if __name__ == "__main__":
    main()
