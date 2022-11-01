import csv
import sys


def main():
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py .CSVFILE .TXTFILE")

    str_counter = {}
    with open(sys.argv[1], "r") as database:
        reader = csv.reader(database)
        headers = next(reader)

        for header in headers:
            if header != "name":
                str_counter[header] = 0

    with open(sys.argv[2], "r") as text_file:
        dna = text_file.readline()

    for str in str_counter:
        str_counter[str] = longest_match(dna, str)

    result = "No match"
    with open(sys.argv[1], "r") as database:
        rows = csv.DictReader(database)

        for row in rows:
            all_values_equal = True

            for str in str_counter:
                if (int(row[str]) != str_counter[str]):
                    all_values_equal = False
                    break

            if (all_values_equal):
                result = row["name"]
                break

    print(result)


def longest_match(sequence, subsequence):
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    for i in range(sequence_length):
        count = 0

        while True:
            start = i + count * subsequence_length
            end = start + subsequence_length

            if sequence[start:end] == subsequence:
                count += 1
            else:
                break

        longest_run = max(longest_run, count)

    return longest_run


if __name__ == "__main__":
    main()
