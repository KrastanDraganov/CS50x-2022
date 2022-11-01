#include <cs50.h>
#include <stdio.h>

int sumDigits(int);
int countDigits(long);
long degreeOf10(int);

int calculateChecksum(long);

bool isAMEX(long);
bool isMASTERCARD(long);
bool isVISA(long);

void determineCreditCard(long);

int main(void)
{
    long creditCardNumber = get_long("Number: ");

    determineCreditCard(creditCardNumber);
}

int sumDigits(int number)
{
    int sum = 0;

    while (number > 0)
    {
        sum += (number % 10);
        number /= 10;
    }

    return sum;
}

int countDigits(long number)
{
    if (number == 0)
    {
        return 1;
    }

    int counter = 0;

    while (number > 0)
    {
        ++counter;
        number /= 10;
    }

    return counter;
}

long degreeOf10(int degree)
{
    long result = 1;

    for (int i = 0; i < degree; ++i)
    {
        result *= 10;
    }

    return result;
}

int calculateCheckSum(long creditCardNumber)
{
    int checksum = 0;

    for (int pos = 0; creditCardNumber > 0; ++pos)
    {
        int currentDigit = creditCardNumber % 10;
        creditCardNumber /= 10;

        if (pos % 2 == 0)
        {
            checksum += currentDigit;
        }
        else
        {
            checksum += sumDigits(2 * currentDigit);
        }
    }

    return checksum;
}

bool isAMEX(long creditCardNumber)
{
    if (countDigits(creditCardNumber) != 15)
    {
        return false;
    }

    int firstDigit = creditCardNumber / degreeOf10(14);
    int secondDigit = (creditCardNumber / degreeOf10(13)) % 10;

    return (firstDigit == 3 && (secondDigit == 4 || secondDigit == 7));
}

bool isMASTERCARD(long creditCardNumber)
{
    if (countDigits(creditCardNumber) != 16)
    {
        return false;
    }

    int firstDigit = creditCardNumber / degreeOf10(15);
    int secondDigit = (creditCardNumber / degreeOf10(14)) % 10;

    return (firstDigit == 5 && (secondDigit == 1 || secondDigit == 2 || secondDigit == 3 || secondDigit == 4 || secondDigit == 5));
}

bool isVISA(long creditCardNumber)
{
    if (countDigits(creditCardNumber) != 13 && countDigits(creditCardNumber) != 16)
    {
        return false;
    }

    int firstDigit = -1;
    if (countDigits(creditCardNumber) == 13)
    {
        firstDigit = creditCardNumber / degreeOf10(12);
    }
    else
    {
        firstDigit = creditCardNumber / degreeOf10(15);
    }

    return (firstDigit == 4);
}

void determineCreditCard(long creditCardNumber)
{
    int checkSum = calculateCheckSum(creditCardNumber);

    if (checkSum % 10 != 0)
    {
        printf("INVALID\n");
        return;
    }


    if (isAMEX(creditCardNumber))
    {
        printf("AMEX\n");
    }
    else if (isMASTERCARD(creditCardNumber))
    {
        printf("MASTERCARD\n");
    }
    else if (isVISA(creditCardNumber))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
