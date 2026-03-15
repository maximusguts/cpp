#include <iostream>

using namespace std;

int main()
{
    int A;
    cout << "enter a number: ";
    cin >> A;
    cout << "\n";

    if (A < 0) {A = -A;}

    for (int B = -A; B < A; B++)
    {
        if (B == 0) {continue;}
        if (A % (B*B) == 0 && A % (B*B*B) != 0)
        {
            cout << B << "\n";
        }
    }
    return 0;
}