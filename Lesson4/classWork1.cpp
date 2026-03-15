#include <iostream>
using namespace std;

int main() {
    char symbol;

    cout << "Enter a symbol: ";
    cin >> symbol;

    const short SIZE = 5;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << symbol << " ";
        }
        cout << endl;   
    }
}
