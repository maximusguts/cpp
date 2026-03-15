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

template <typename T>
double Arithmetic_mean (T list[], int size) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += double(list[i]);
    }
    return sum / double(size);
}

template <typename T>
T degree(T x, int y) {
    T result = 1;
    if (y < 0) {
        x = 1 / x;
        y = -y;
    }

    for (int i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}

void Print(int x) {
    cout << x << endl;
}

void Print(double x) {
    cout << x << endl;
}

void Print(char x) {
    cout << x << endl;
}

void Print(string x) {
    cout << x << endl;
}

template <typename T>
void Print(T x [], int size) {
    for (int i = 0; i < size; i++) {
        cout << x[i] << " ";
    }
    cout << endl;
}

template <typename T>
T Abs(T x) {
    if (x < 0) {
        return -x;
    }
    return x;
}

bool id_is_exist(int id, int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == id) return true;
    }
    return false;
}

template <typename T>
void Shufle_Array(T arr[], int size) {
    int indxs[size] = {};
    for (int i = 0; i < size; ++i)
    indxs[i] = -1;
    for (int i = 0; i < size; i++) {
        while (true) {
            int rand_index = rand() % size;
            if (!id_is_exist(rand_index, indxs, size)) {
                indxs[i] = rand_index;
                break;
            }
        }
    }
    T newArr[size] = {};
    for (int i = 0; i < size; i++) {
        newArr[i] = arr[indxs[i]];
    }
    for (int i = 0; i < size; i++) {
    arr[i] = newArr[i];
    }
}

template <typename T>
void count_of_diffrent_numbers(T arr[], int size) {
    int count_of_zeros = 0;
    int count_of_positives = 0;
    int count_of_negatives = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == 0) {
            count_of_zeros++;
        }
        else if (arr[i] > 0) {
            count_of_positives++;
        }
        else {
            count_of_negatives++;
        }
    }
    Print("Count of zeros: " + to_string(count_of_zeros));
    Print("Count of positives: " + to_string(count_of_positives));
    Print("Count of negatives: " + to_string(count_of_negatives));
}

int main()
{
    srand(time(NULL));
    
    double list[10] = { 1.2, 2.3, -3.4, 0, 5.6, -6.7, -7.8, -8.9, 0, 10.1 };
    count_of_diffrent_numbers(list, 10);

    return 0;
}