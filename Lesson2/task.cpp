#include <iostream>

using namespace std;

int main()
{
    int n;
    cout << "Enter a 6-digit number: ";
    cin >> n;
    cout << "\n";
    
    if (n >= 100000 && n <= 999999)
    {
        int n1 = (n / 100000) % 10;
        int n2 = (n / 10000) % 10;
        int n3 = (n / 1000) % 10;
        int n4 = (n / 100) % 10;
        int n5 = (n / 10) % 10;
        int n6 = n % 10;

        int s1 = n1 + n2 + n3;
        int s2 = n4 + n5 + n6;

        if (s1 == s2)
        {
            cout << "Your number is a happy number 😊" << endl;
        }
        else
        {
            cout << "Your number is NOT a happy number 😞" << endl;
        }
    }
    else
    {
        cout << "Your number is not a 6-digit number!" << endl;
    }

    return 0;
}