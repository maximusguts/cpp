#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

void Swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

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

int* Allocate(int size)
{
	return new int[size];
}

void Init(int* p, int size)
{
	for (int i = 0; i < size; i++)
	{
		*p = rand() % 100;
		p++;
	}
}

int** AddStringEnd(int** ptr, int* row, int col, int* mas)
{
	*row = *row + 1;
	int** p_new = new int* [*row];

	for (int i = 0; i < *row - 1; i++)
		p_new[i] = ptr[i];

	delete[] ptr;

	p_new[*row - 1] = Allocate(col);

	for (int j = 0; j < col; j++)
		p_new[*row - 1][j] = mas[j];


	return p_new;
}

int** RemoveStringStart(int** ptr, int* row)
{
	*row = *row - 1;
	int** p_new = new int* [*row];

	for (int i = 0; i < *row; i++)
		p_new[i] = ptr[i+1];

	delete[] ptr[0];
	delete[] ptr;

	return p_new;
}

void AddColumnEnd(int**& ptr, int row, int& col, int* mas2)
{
	col++;
	int** p_new = Allocate(row, col);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col - 1; j++)
		{
			p_new[i][j] = ptr[i][j];
		}
		p_new[i][col - 1] = mas2[i];
	}

	Free(ptr, row);
	ptr = p_new;
}

void AddColumnIndex(int**& ptr, int row, int& col, int* mas2, int index)
{
	if (index < 0 || index >= col)
	{
		return;
	}
	col++;
	int** p_new = Allocate(row, col);

	int k = 0;
	for (int i = 0; i < row; i++)
	{
		k = 0;
		for (int j = 0; j < col; j++)
		{
			if (j == index)
				k = 1;
			else
				p_new[i][j] = ptr[i][j-k];
		}
		
	}

	for (int i = 0; i < row; i++)
		p_new[i][index] = mas2[i];

	Free(ptr, row);
	ptr = p_new;

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

void Delete_column_by_index(int**& a, int row, int& col, int index) {
    if (index < 0 || index >= col) {
        return;
    }
    
    col--;
    int** new_a = Allocate(row, col);

    for (int i = 0; i < row; i++) {
        int k = 0;
        for (int j = 0; j < col + 1; j++) {
            if (j == index) {
                k = 1;
            } else {
                new_a[i][j - k] = a[i][j];
            }
        }
    }

    Free(a, row);
    a = new_a;
}

void Delete_string_by_index(int**& a, int& row, int col, int index) {
    if (index < 0 || index >= row) {
        return;
    }
    
    row--;
    int** new_a = Allocate(row, col);

    for (int i = 0; i < row + 1; i++) {
        if (i < index) {
            for (int j = 0; j < col; j++) {
                new_a[i][j] = a[i][j];
            }
        } else if (i > index) {
            for (int j = 0; j < col; j++) {
                new_a[i - 1][j] = a[i][j];
            }
        }
    }

    Free(a, row + 1);
    a = new_a;
}

void Transposition(int**& a, int& row, int& col) {
    Swap(row, col);
    int** new_a = Allocate(row, col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            new_a[i][j] = a[j][i];
        }
    }

    Free(a, col);
    a = new_a;
}

int main()
{
    srand(time(NULL));
    
    int row = 10, col = 15;
    int** matrix = Allocate(row, col);
    Init(matrix, row, col);
    Print(matrix, row, col);
    cout << endl;

    cout << "Enter an index to delete a column: ";
    int index;
    cin >> index;
    Delete_column_by_index(matrix, row, col, index);
    Print(matrix, row, col);
    cout << endl;

    cout << "Enter an index to delete a string: ";
    cin >> index;
    Delete_string_by_index(matrix, row, col, index);
    Print(matrix, row, col);
    cout << endl;

    cout << "Transposed matrix:" << endl;
    Transposition(matrix, row, col);
    Print(matrix, row, col);
    cout << endl;

    Free(matrix, row);

    return 0;
}