#include <iostream>
#include "Windows.h"

using namespace std;


int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);


    float a, b, c;

    cout << "привіт" << endl;

    int n1, n2, n3;

    cout << "enter 3 numbers: ";
    cin >> n1 >> n2 >> n3;
    cout << (n1 + n2 + n3) / 3 << endl;

    cout << "\n";

    cout << "Enter a, b, c:";
    cin >> a >> b >> c;

    float v = a * b * c;

    cout << "Solution: " << v << endl;


    // cout << "Hello World" << endl;
    // cout << "What is tour name?" << endl;


    return 0;
}
