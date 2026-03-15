#include <iostream>

using namespace std;

int main()
{
    bool a_ready = false;
    int a;
    
    while (!a_ready)
    {
        cout << "enter an a - ";
        cin >> a;
        cout << "\n";

        if (a > 20 || a < 1)
        {
            cout << "a is not an avaible.\n";
        }
        else
        {
            a_ready = true;
        }
    }

    int product = 1;

    for (int i = a; i < 21; i++)
    {
        product *= i;
    }

    cout << "the product of different iterations is: " << product;
}