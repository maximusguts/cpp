#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

int Round(double x) {
    if (x - int(x) >= 0.5) {
        return int(x) + 1;
    }
    else {
        return x;
    }
}

int main()
{
    srand(time(NULL));
    
    const int ROWS_l1 = 5;
    const int COLS_l1 = 10;
    const int range_l1 = 50;

    const int ROWS_l2 = 5;
    const int COLS_l2 = 5;

    int arr1[ROWS_l1][COLS_l1] = {};
    int arr2[ROWS_l2][COLS_l2] = {};

    for (int i = 0; i < ROWS_l1; i++)
    {
        for (int j = 0; j < COLS_l1; j++)
        {
            arr1[i][j] = rand() % range_l1 + 1;
            cout << setw(4) << arr1[i][j] << " ";

            if (j % 2 != 0) {
                arr2[i][j / 2] = arr1[i][j] + arr1[i][j - 1];
            }
        }
        cout << endl;
    }
    
    cout << "-------------------------" << endl;

    for (int i = 0; i < ROWS_l2; i++)
    {
        for (int j = 0; j < COLS_l2; j++)
        {
            cout << setw(4) << arr2[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}