from cs50 import get_int


def main():
    while True:
        height = get_int("Height: ")
        if height in range(1, 9):
            break

    for cells in range(1, height + 1):
        spaces = height - cells

        print(" " * spaces, end="")
        print("#" * cells, end="")

        print("  ", end="")

        print("#" * cells)


if __name__ == "__main__":
    main()
