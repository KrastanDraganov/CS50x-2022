#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool contain_all_letters(string key);
string get_text_ciphered(string text, string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    if (!contain_all_letters(key))
    {
        printf("Key must contain 26 unique letters\n");
        return 1;
    }

    string plaintext = get_string("plaintext: ");
    string ciphertext = get_text_ciphered(plaintext, key);

    printf("ciphertext: %s\n", ciphertext);
}

bool contain_all_letters(string key)
{
    if (strlen(key) != 26)
    {
        return false;
    }

    bool usedLetter[26];
    for (int i = 0; i < 26; ++i)
    {
        usedLetter[i] = false;
    }

    for (int i = 0; i < 26; ++i)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }

        int currentLetter = tolower(key[i]) - 'a';

        if (usedLetter[currentLetter])
        {
            return false;
        }

        usedLetter[currentLetter] = true;
    }

    return true;
}

string get_text_ciphered(string text, string key)
{
    int len = strlen(text);

    for (int i = 0; i < len; ++i)
    {
        if (!isalpha(text[i]))
        {
            continue;
        }

        int currentLetter = tolower(text[i]) - 'a';

        if (islower(text[i]))
        {
            text[i] = tolower(key[currentLetter]);
        }
        else
        {
            text[i] = toupper(key[currentLetter]);
        }
    }

    return text;
}
