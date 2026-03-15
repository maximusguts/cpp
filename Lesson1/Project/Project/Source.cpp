#include <iostream>
#include "Windows.h"

using namespace std;

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

    cout << "enter seconds: ";
    double s_inp;
    cin >> s_inp;

    int h = s_inp / 3600.0;
    int m = (s_inp - h * 3600) / 60.0;
    int s = s_inp - h * 3600 - m * 60;

    cout << "hours:" << h << " minutes:" << m << " seconds:" << s << "\n";

	return 0;
}
