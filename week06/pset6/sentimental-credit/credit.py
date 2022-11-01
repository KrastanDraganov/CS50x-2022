from cs50 import get_int


def main():
    creditCardNumber = get_int("Number: ")
    creditCard = determineCreditCard(creditCardNumber)
    print(creditCard)


def sumDigits(number):
    sum = 0

    for digit in str(number):
        sum += int(digit)

    return sum


def calculateCheckSum(number):
    checksum = 0
    digitsCount = len(str(number))

    for pos in range(digitsCount):
        currentDigit = number % 10
        number //= 10

        if pos % 2 == 0:
            checksum += currentDigit
        else:
            checksum += sumDigits(2 * currentDigit)

    return checksum


def isAMEX(creditCardNumber):
    if len(str(creditCardNumber)) != 15:
        return False

    firstDigit = int(str(creditCardNumber)[0])
    secondDigit = int(str(creditCardNumber)[1])

    return firstDigit == 3 and (secondDigit == 4 or secondDigit == 7)


def isMASTERCARD(creditCardNumber):
    if len(str(creditCardNumber)) != 16:
        return False

    firstDigit = int(str(creditCardNumber)[0])
    secondDigit = int(str(creditCardNumber)[1])

    return firstDigit == 5 and (secondDigit in range(1, 6))


def isVISA(creditCardNumber):
    digitCount = len(str(creditCardNumber))
    if digitCount != 13 and digitCount != 16:
        return False

    firstDigit = int(str(creditCardNumber)[0])

    return firstDigit == 4
    

def determineCreditCard(creditCardNumber):
    if calculateCheckSum(creditCardNumber) % 10 != 0:
        return "INVALID"

    if isAMEX(creditCardNumber):
        return "AMEX"
    elif isMASTERCARD(creditCardNumber):
        return "MASTERCARD"
    elif isVISA(creditCardNumber):
        return "VISA"

    return "INVALID"


if __name__ == "__main__":
    main()
