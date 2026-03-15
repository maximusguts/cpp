#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

int main() {

    const int ROWS = 3;
    const int COLS = 4;
    const int range = 20;

    srand(time(NULL));

    int arr[ROWS][COLS] ={};

    int sum = 0;

    for (int i = 0; i < ROWS; i++)
    {
        int t_sum = 0;
        for (int j = 0; j < COLS; j++)
        {
            arr[i][j] = rand() % range;

            t_sum += arr[i][j];

            cout << setw(4) << arr[i][j] << " ";
        }
        sum += t_sum;
        cout << "| " << t_sum << endl;
    }

    cout << "-------------------------" << endl;

    for (int j = 0; j < COLS; j++)
    {
        int t_sum2 = 0;
        for (int i = 0; i < ROWS; i++)
        {
            t_sum2 += arr[i][j];
        }
        cout << setw(4) << t_sum2 << " ";
    }
    cout << "| " << sum << endl;

    return 0;
}