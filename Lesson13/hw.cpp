#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

int** Allocate(int row, int col)
{
	int** p = new int* [row];

	for (int i = 0; i < row; i++)
		p[i] = new int[col];

	return p;
}

void Init(int** ptr, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			ptr[i][j] = rand() % 41 - 20; // -20...20
		}
	}
}


void Print(int** ptr, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << setw(5) << ptr[i][j];
		}
		cout << endl;
	}
}

void Print(int* ptr, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << setw(5) << ptr[i];
    }
    cout << endl;
}

void Free(int** ptr, int row)
{
	for (int i = 0; i < row; i++)
		delete ptr[i];

	delete[] ptr;
}

int Sum_of_elements(int** a, int row, int col) {
    int sum = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            sum += a[i][j];
        }
    }
    
    return sum;
}

void Search_different_elements(int** a, int row, int col,
                               int*& neg, int& neg_size,
                               int*& pos, int& pos_size,
                               int*& zero, int& zero_size)
{
    neg_size = 0;
    pos_size = 0;
    zero_size = 0;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (a[i][j] < 0) {
                neg_size++;
            } else if (a[i][j] > 0) {
                pos_size++;
            } else {
                zero_size++;
            }
        }
    }

    neg = new int[neg_size];
    pos = new int[pos_size];
    zero = new int[zero_size];

    neg_size = 0;
    pos_size = 0;
    zero_size = 0;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (a[i][j] < 0) {
                neg[neg_size++] = a[i][j];
            } else if (a[i][j] > 0) {
                pos[pos_size++] = a[i][j];
            } else {
                zero[zero_size++] = a[i][j];
            }
        }
    }
}

void Delete_last_row(int**& a, int& row, int col) {
    if (row <= 0) return;

    int** new_a = new int*[row - 1];
    for (int i = 0; i < row - 1; i++) {
        new_a[i] = new int[col];
        for (int j = 0; j < col; j++) {
            new_a[i][j] = a[i][j];
        }
    }

    Free(a, row);
    a = new_a;
    row--;
}


int main()
{
    srand(time(NULL));
    
    int row = 10, col = 10;
    int** matrix = Allocate(row, col);
    Init(matrix, row, col);
    Print(matrix, row, col);
    cout << endl;

    cout << "Sum of elements: " << Sum_of_elements(matrix, row, col) << endl;
    cout << endl;

    int* neg = nullptr, * pos = nullptr, * zero = nullptr;
    int neg_size = 0, pos_size = 0, zero_size = 0;
    Search_different_elements(matrix, row, col, neg, neg_size, pos, pos_size, zero, zero_size);
    cout << "Negative elements: ";
    Print(neg, neg_size);
    cout << endl;
    cout << "Positive elements: ";
    Print(pos, pos_size);
    cout << endl;
    cout << "Zero elements: ";
    Print(zero, zero_size);
    cout << endl;

    Delete_last_row(matrix, row, col);
    cout << "Matrix after deleting the last row:" << endl;
    Print(matrix, row, col);
    cout << endl;
    
    Free(matrix, row);
    delete[] neg;
    delete[] pos;
    delete[] zero;
    cout << "Memory freed successfully." << endl;

    return 0;
}