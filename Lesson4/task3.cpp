#include <iostream>

using namespace std;

int main() {

    const int n_SIZE = 30;
    const int range = 10000;

    int numbers[n_SIZE];
    // {
    //     rand() % 100, rand() % 100, rand() % 100,
    //     rand() % 100, rand() % 100, rand() % 100,
    //     rand() % 100, rand() % 100, rand() % 100,
    //     rand() % 100, rand() % 100, rand() % 100
    // };
    
    for (int i = 0; i < n_SIZE; i++)
    {
        int pls_mns = rand() % 2;

        if (pls_mns == 0)
        {
            numbers[i] = rand() % range;
        }
        else
        {
            numbers[i] = -rand() % range;
        }
    }

    int maximum = numbers[0];
    int minimum = numbers[0];
    int sum_of_negtiv = 0;
    int prod_of_even = 1;
    int sum_between_negtiv = 0;
    int first_negative = 0;
    int last_negative = 0;

    for (int i = 0; i < n_SIZE; i++)
    {
        cout << numbers[i] << " ";

        if (numbers[i] < 0 && first_negative == 0)
        {
            first_negative = numbers[i];
        }
        if (numbers[i] < 0)
        {
            last_negative = numbers[i];
        }

        if (numbers[i] % 2 == 0)
        {
            prod_of_even *= numbers[i];
        }

        if (numbers[i] < 0)
        {
            sum_of_negtiv += numbers[i];
        }

        if (numbers[i] > maximum)
        {
            maximum = numbers[i];
        }

        if (numbers[i] < minimum)
        {
            minimum = numbers[i];
        }
    }
    cout << "\n\n";

    int prod_mode = 0;
    int product = 1;
    int sum_mode = 0;

    for (int i = 0; i < n_SIZE; i++)
    {
        if (numbers[i] == first_negative || numbers[i] == last_negative)
        {
            sum_mode += 1;
        }
        if (sum_mode == 1)
        {
            sum_between_negtiv += numbers[i];
        }

        if (numbers[i] == maximum || numbers[i] == minimum)
        {
            prod_mode += 1;
        }
        if (prod_mode == 1)
        {
            product *= numbers[i];
        }
    }

    cout << "Sum of negative numbers: " << sum_of_negtiv << "\n";
    cout << "Product of numbers between maximum and minimum: " << product << "\n";
    cout << "Maximum: " << maximum << "\n";
    cout << "Minimum: " << minimum << "\n";
    cout << "Product of even numbers: " << prod_of_even << "\n";
    cout << "Sum of numbers between first and last negative: " << sum_between_negtiv << "\n";
    cout << "First negative number: " << first_negative << "\n";
    cout << "Last negative number: " << last_negative << "\n";
    
}