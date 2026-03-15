#include <iostream>

using namespace std;

int main()
{
    int n;

    cout << "enter a 4-digit number: ";
    cin >> n;
    cout << "\n";
    
    if (!(n > 999 && n < 10000))
    {
        cout << "you'r number is not 4-digit";
        return 0;
    }
    
    int n1 = (n / 1000) % 10;
    int n2 = (n / 100) % 10;
    int n3 = (n / 10) % 10;
    int n4 = n % 10;

    // int n_list[4] = { n1, n2, n3, n4 };
    // cout << n_list[0] << "\n" << n_list[1] << "\n" << n_list[2] << "\n" << n_list[3] << "\n";
    
    int total_n = n2 * 1000 + n1 * 100 + n4 * 10 + n3;
    cout << total_n;
    
    return 0;
}