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

double Arithmetic_mean (int list[], int size) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += double(list[i]);
    }
    return sum / double(size);
}

double Arithmetic_mean (float list[], int size) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += double(list[i]);
    }
    return sum / double(size);
}

double Arithmetic_mean (double list[], int size) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += list[i];
    }
    return sum / double(size);
}

template <typename T>
void Print(T x) {
    cout << x << endl;
}

template <typename T>
T Abs(T x) {
    if (x < 0) {
        return -x;
    }
    return x;
}

int how_many_days(int year, int mounth) {
    if (mounth == 2) {
            if (year % 4 == 0) {
                return 29;
            }
            else {
                return 28;
            }
        }
        else if (mounth == 4 || mounth == 6 || mounth == 9 || mounth == 11) {
            return 30;
        }
        else {
            return 31;
        }
}

int count_of_days_in_year(int day, int month, int year) {
    int days = 0;
    for (int i = 1; i < month; i++) {
        days += how_many_days(year, i);
    }
    days += day;
    return days;
}

int date_difference(int day1, int month1, int year1, int day2, int month2, int year2) {
    int year_difference = year2 - year1;
    int days1 = count_of_days_in_year(day1, month1, year1);
    int days2 = count_of_days_in_year(day2, month2, year2);
    int dif = (days2 - days1) + (year_difference * 365.25);
    return Abs(dif);
}

void show_result(int days) {
    cout << "Difference in days: " << days << endl;
    
    double c_days[12] = { 31.0, 28.25, 31.0, 30.0, 31.0, 30.0, 31.0, 31.0, 30.0, 31.0, 30.0, 31.0 };
    double months = double(days) / Arithmetic_mean(c_days, 12);
    
    cout << "Difference in months: " << months << endl;
    
    double years = double(days) / 365.25;
    
    cout << "Difference in years: " << years << endl;
}

int main()
{
    srand(time(NULL));
    
    cout << "Enter first date (day month year): ";
    int day1 = 0, month1 = 0, year1 = 0;
    cin >> day1 >> month1 >> year1;
    cout << "Enter second date (day month year): ";
    int day2 = 0, month2 = 0, year2 = 0;
    cin >> day2 >> month2 >> year2;
    int result = date_difference(day1, month1, year1, day2, month2, year2);
    
    show_result(result);
    
    return 0;
}