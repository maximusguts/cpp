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

void inicialization_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
}

void inicialization_array(double arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = double(rand() % 10000) / 1000;
    }
}

void inicialization_array(char arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = 'A' + rand() % 26;
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

void Free(int* p)
{
    delete[] p;
}

void Free(int** p, int row)
{
	for (int i = 0; i < row; i++)
		Free(p[i]);
	delete[] p;
}

void Copy_array(int *arr1, int *arr2, int size) {
    for (int i = 0; i < size; i++) {
        *arr2 = *arr1;
        arr2++;
        arr1++;
    }
}

void Reverse_array(int *ptr, int size) {
    int left = 0;
    int right = size - 1;
    while (left < right) {
        int temp = ptr[left];
        ptr[left] = ptr[right];
        ptr[right] = temp;
        left++;
        right--;
    }
}

void Copy_reverse_array(int *arr1, int *arr2, int size) {
    Copy_array(arr1, arr2, size);
    Reverse_array(arr2, size);
}

int main()
{
    srand(time(NULL));
    
    const int SIZE = 5;

    int arr[SIZE];
    inicialization_array(arr, 5);
    Print("Array 1 before copy: ");
    Print(arr, 5);

    int *ptr = arr;
    int *ptr2 = nullptr;
    
    int arr2[SIZE];
    inicialization_array(arr2, 5);
    Print("Array 2 before copy: ");
    Print(arr2, 5);
    Print();

    ptr2 = arr2;

    Copy_array(ptr, ptr2, SIZE);
    // Copy_array(&arr[0], &arr2[0], SIZE);
    
    Print("Array 1 after copy: ");
    Print(arr, 5);
    Print("Array 2 after copy: ");
    Print(arr2, 5);
    Print();
    Print();


    int arr3[10];
    inicialization_array(arr3, 10);
    cout << "Original array: ";
    Print(arr3, 10);
    Sort(arr3, 10);
    cout << "Sorted array: ";
    Print(arr3, 10);
    Reverse_array(arr3, 10);
    cout << "Reversed array: ";
    Print(arr3, 10);
    Print();
    Print();
    
    int arr4[10];
    inicialization_array(arr4, 10);
    int arr5[10];
    inicialization_array(arr5, 10);
    cout << "Array 1: ";
    Print(arr4, 10);
    cout << "Array 2: ";
    Print(arr5, 10);
    Copy_reverse_array(arr4, arr5, 10);
    Print();

    cout << "After copying and reversing:" << endl;
    Print();

    cout << "Array 1: ";
    Print(arr4, 10);
    cout << "Array 2: ";
    Print(arr5, 10);
    Print();

    return 0;
}