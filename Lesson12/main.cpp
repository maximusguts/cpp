#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

int mystrcmp (const char * str1, const char * str2) {
    int str1_len = 0;
    int str2_len = 0;

    while ((str1[str1_len] != '\0') || (str2[str2_len] != '\0')) {
        str1_len++;
        str2_len++;
    }

    if (str1_len < str2_len) {
        return -1; // str1 is shorter than str2
    } else if (str1_len > str2_len) {
        return 1; // str1 is longer than str2
    } else {
        return 0; // str1 and str2 are of equal length
    }
}

int StringToNumber(char * str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') {
        sign = -1;
        i++;
    } else if (str[0] == '+') {
        i++;
    }

    for (; str[i] != '\0'; i++) {
        if (str[i] < '0' && str[i] > '9') {
            return 0; // Invalid character found
        }
        result = result * 10 + (str[i] - '0');
    }

    return result * sign;
}

char * NumberToString (int number) {
    static char buffer[12]; // Enough for 32-bit int
    int index = 0;
    bool is_negative = false;

    if (number < 0) {
        is_negative = true;
        number = -number;
    }

    do {
        buffer[index++] = (number % 10) + '0';
        number /= 10;
    } while (number > 0);

    if (is_negative) {
        buffer[index++] = '-';
    }

    buffer[index] = '\0';

    // Reverse the string
    for (int i = 0; i < index / 2; i++) {
        char temp = buffer[i];
        buffer[i] = buffer[index - i - 1];
        buffer[index - i - 1] = temp;
    }

    return buffer;
}

char * Uppercase (char * str1) {
    for (int i = 0; str1[i] != '\0'; i++) {
        if (str1[i] >= 'a' && str1[i] <= 'z') {
            str1[i] -= 32;
        }
    }
    return str1;
}

char * Lowercase (char * str1) {
    for (int i = 0; str1[i] != '\0'; i++) {
        if (str1[i] >= 'A' && str1[i] <= 'Z') {
            str1[i] += 32;
        }
    }
    return str1;
}

char * mystrrev (char * str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }

    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }

    return str;
}

int main()
{
    srand(time(NULL));
    
    char str1[] = "Hello";
    char str2[] = "World";
    cout << "Comparing \"" << str1 << "\" and \"" << str2 << "\": " << mystrcmp(str1, str2) << endl;
    char numStr[] = "-12345";
    cout << "String to number conversion of \"" << numStr << "\": " << StringToNumber(numStr) << endl;
    int number = -6789;
    cout << "Number to string conversion of " << number << ": " << NumberToString(number) << endl;
    char str3[] = "hello world";
    cout << "Uppercase of \"" << str3 << "\": " << Uppercase(str3) << endl;
    char str4[] = "HELLO WORLD";
    cout << "Lowercase of \"" << str4 << "\": " << Lowercase(str4) << endl;
    char str5[] = "abcdef";
    cout << "Reversed string of \"" << str5 << "\": " << mystrrev(str5) << endl;

    return 0;
}