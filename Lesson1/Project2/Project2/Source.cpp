#include <iostream>
#include "Windows.h"

using namespace std;

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    cout << "enter seconds from starting a work day: ";
    double s_inp;
    cin >> s_inp;
    double s_remain = 8 * 3600.0 - s_inp;

    if (s_remain <= 0)
    {
        cout << "the work day is already end!";
    }

    else
    {
        int h = s_remain / 3600.0;
        int m = (s_remain - h * 3600) / 60.0;
        int s = s_remain - h * 3600 - m * 60;

        cout << "remained hours:" << h << ", minutes:" << m << ", and seconds:" << s << "\n";
    }

    return 0;
}
