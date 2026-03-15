#include <iostream>

using namespace std;

int main()
{
    int n1, n2, n3, n4, n5, n6, n7;

    cout << "enter a 7 ineger numbers: ";
    cin >> n1 >> n2 >> n3 >> n4 >> n5 >> n6 >> n7;
    cout << "\n";
    
    int max = n1;
    
    if (n2 > max) max = n2;
    if (n3 > max) max = n3;
    if (n4 > max) max = n4;
    if (n5 > max) max = n5;
    if (n6 > max) max = n6;
    if (n7 > max) max = n7;

    // int n_list[7] = { n1, n2, n3, n4, n5, n6, n7 };
    // cout << n_list[0] << "\n" << n_list[1] << "\n" << n_list[2] << "\n" << n_list[3] << "\n" << n_list[4] << "\n" << n_list[5] << "\n" << n_list[6] << "\n";
    
    cout << "maximum number betwen you'rs 7 numbers is " << max;
    
    return 0;
}