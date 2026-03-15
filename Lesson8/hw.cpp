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

void Print() {
    cout << endl;
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

template <typename T, int N>
void Print(T x [][N], int size1, int size2) {
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            cout << x[i][j] << " ";
        }
        cout << endl;
    }
    
}

template <typename T, int N1, int N2>
void Print(T x [][N1][N2], int size1, int size2, int size3) {
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            for (int k = 0; k < size3; k++) {
                cout << x[i][j][k] << " ";
            }
            cout << "   ";
        }
        cout << endl;
    }
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

template <int N>
void inicialization_square_matrix(int a[][N], int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            a[i][j] = rand() % 10;
        }
    }
}

template <int N>
void inicialization_square_matrix(double a[][N], int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            a[i][j] = double(rand() % 10000) / 1000;
        }
    }
}

template <int N>
void inicialization_square_matrix(char a[][N], int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            a[i][j] = 'A' + rand() % 26;
        }
    }
}

template <int N>
void max_min_from_diagonal(int a[][N], int r, int c) {
    int min = a[0][0];
    int max = a[0][0];
    int min_direction = r < c ? r : c;

    for (int i = 0; i < min_direction; i++) {
        if (a[i][i] < min) {
            min = a[i][i];
        }
        if (a[i][i] > max) {
            max = a[i][i];
        }
    }
    Print("Min: " + to_string(min));
    Print("Max: " + to_string(max));
}

void Sort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void Sort(double arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void Sort(char arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                char temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

template <int N>
void Sort_Square_Matrix(int arr[][N], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        Sort(arr[i], cols);
    }
}

template <int N>
void Sort_Square_Matrix(double arr[][N], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        Sort(arr[i], cols);
    }
}

template <int N>
void Sort_Square_Matrix(char arr[][N], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        Sort(arr[i], cols);
    }
}

int main()
{
    srand(time(NULL));
    
    const int rows = 10;
    const int cols = 10;
    int arr[rows][cols];

    inicialization_square_matrix(arr, rows, cols);
    cout << "Square matrix:\n";
    Print(arr, rows, cols);
    Print();
    Print("Max and min from diagonal:");
    max_min_from_diagonal(arr, rows, cols);

    Print();
    Print("Sorted square matrix:");
    Sort_Square_Matrix(arr, rows, cols);
    Print(arr, rows, cols);
    Print();

    return 0;
}