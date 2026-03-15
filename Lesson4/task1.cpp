#include <iostream>

using namespace std;

int main() {

    const int n_SIZE = 30;
    const int range = 1000;

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

    for (int i = 0; i < n_SIZE; i++)
    {
        cout << numbers[i] << " ";

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

    cout << "Maximum: " << maximum << "\n";
    cout << "Minimum: " << minimum << "\n";

    return 0;
}