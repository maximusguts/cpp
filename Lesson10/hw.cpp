#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

void Swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

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

int* Allocate(int size)
{
	return new int[size];
}

void Free(int* p)
{
	delete[] p;
}

int* Add(int* p, int* size, int value)
{
	(*size)++;

	int* p_new = new int[*size];

	for (int i = 0; i < (*size - 1); i++)
	{
		p_new[i] = p[i];
	}

	p_new[*size - 1] = value;

	Free(p);

	return p_new;

}

int Sum(int* p, int size)
{
    int sum = 0;

    for (int i = 0; i < size; i++)
    {
        sum += p[i];
    }

    return sum;
}

int* Add_sum_to_end(int* p, int* size)
{
	(*size)++;

	int* p_new = new int[*size];

	for (int i = 0; i < (*size - 1); i++)
	{
		p_new[i] = p[i];
	}

	p_new[*size - 1] = Sum(p, *size - 1);

	Free(p);

	return p_new;

}

void InsertByIndex(int*& p, int& size, int value, int index)
{
	if (index < 0 || index >= size)
	{
		cout << "error index" << endl;
		return;
	}
 
	size++;
	int* p_new = new int(size);
 
	/*
	for (int i = 0; i < index; i++)
		p_new[i] = p[i];
 
	p_new[index] = value;
 
	for (int i = index+1; i < size; i++)
		p_new[i] = p[i-1];
	*/
 
	int k = 0; // зміщення
	for (int i = 0; i < size; i++)
	{
		if (i == index)
		{
			k = 1;
			p_new[i] = value;
		}
		else
			p_new[i] = p[i - k];
	}
 
	Free(p);
	p = p_new;
}

void Init(int* p, int size)
{
    for (int i = 0; i < size; i++)
    {
        p[i] = rand() % 100;
    }
}

void Delete_last_element(int*& p, int& size) {
    if (size <= 0) {
        cout << "Array is empty, cannot delete last element." << endl;
        return;
    }
    size--;
    int* p_new = new int[size];
    for (int i = 0; i < size; i++) {
        p_new[i] = p[i];
    }
    Free(p);
    p = p_new;
}

void Deletete_element_by_index(int *&p, int &size, int index) {
    if (index < 0 || index >= size) {
        cout << "Error: Index out of range." << endl;
        return;
    }
    int* p_new = new int[size - 1];
    for (int i = 0, j = 0; i < size; i++) {
        if (i == index) continue;
        p_new[j++] = p[i];
    }
    Free(p);
    p = p_new;
    size--;
}

int main()
{
    srand(time(NULL));
    
    int* p = nullptr;
    int size;

    cout << "Enter size of array: ";
    cin >> size;
    
    p = Allocate(size);
    Init(p, size);
    Print(p, size);
    Print();
    
    cout << "Enter value to add: ";
    int value;
    cin >> value;
    p = Add(p, &size, value);
    Print(p, size);
    Print();

    cout << "Enter index to insert value: ";
    int index;
    cin >> index;
    cout << "Enter value to insert: ";
    cin >> value;
    InsertByIndex(p, size, value, index);
    Print(p, size);
    Print();
    
    cout << "Sum of array: " << Sum(p, size) << endl;
    p = Add_sum_to_end(p, &size);
    Print(p, size);
    Print();

    cout << "Array after deleting last element: " << endl;
    Delete_last_element(p, size);
    Print(p, size);
    Print();

    cout << "Enter index to delete element: ";
    cin >> index;
    Deletete_element_by_index(p, size, index);
    Print(p, size);
    Print();

    return 0;
}