#include <iostream>
#include "Windows.h"
#include "ddm.h"
using namespace std;

// функції для роботи з динамічним двовимірним масивом


int main()
{
    srand(time(NULL));

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int** ptr = nullptr;

    int row, col;

    cout << "Rows = " << endl;
    cin >> row;

    cout << "Colums = " << endl;
    cin >> col;

    ptr = Allocate(row, col);

    Init(ptr, row, col);
    Print(ptr, row, col);

    Free(ptr, row);
    ptr = nullptr;

    return 0;
}
