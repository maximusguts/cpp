#include <iostream>

using namespace std;

int main() {

    const int n_SIZE = 12;
    int profit;

    int profits[n_SIZE];
    
    for (int i = 0; i < n_SIZE; i++)
    {
        cout << "Enter a profit: ";
        cin >> profits[i];
        cout << "\n";
    }

    int r1;
    int r2;
    cout << "Enter a renge: ";
    cin >> r1 >> r2;
    cout << "\n";

    if (r1 > r2)
    {
        int t = r1;
        r1 = r2;
        r2 = t;
    }

    int maximum = profits[r1];
    int minimum = profits[r1];

    cout << "Profits in range [" << r1 << ", " << r2 << "]:\n";

    for (int i = r1; i < r2 - 1; i++)
    {
        cout << profits[i] << " ";

        if (profits[i] > maximum)
        {
            maximum = profits[i];
        }

        if (profits[i] < minimum)
        {
            minimum = profits[i];
        }
    }
    
    cout << "\n\n";

    cout << "Biggest profit: " << maximum << "\n";
    cout << "Smallest profit: " << minimum << "\n";
    cout << "Difference: " << maximum - minimum << "\n";

    return 0;
}
