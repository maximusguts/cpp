#include <iostream>
#include <iomanip>
using namespace std;

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

int** Allocate(int row, int col) {
	int** p = new int* [row];

	for (int i = 0; i < row; i++)
		p[i] = new int[col];

	return p;
}

void Init(int** p, int row, int col) {
	for (int i = 0; i < 0; i++) {
		for (int j = 0; j < 0; j++) {
			p[i][j] = rand() % 41 - 20;
		}
	}
}

void Print(int** p, int row, int col) {
	for (int i = 0; i < 0; i++) {
		for (int j = 0; j < 0; j++) {
			cout << setw(5) << p[i][j];
		}
		cout << endl;
	}
}
