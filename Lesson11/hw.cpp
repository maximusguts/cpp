#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

int* Allocate(int size)
{
	return new int[size];
}

void Init(int p[], int size)
{
	for (int i=0; i < size; i++)
	{
		*p = rand() % 200 - 100; // Random numbers from -100 to 99
		p++;
	}
}

void Print(int* p, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << p[i] << "  ";
	}

	cout << endl;
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

void InsertByIndex(int*& p, int& size, int value, int index)
{
	if (index < 0 || index >= size)
	{
		cout << "error index" << endl;
		return;
	}

	size++;
	int* p_new = Allocate(size);

	/*
	for (int i = 0; i < index; i++)
		p_new[i] = p[i];

	p_new[index] = value;

	for (int i = index+1; i < size; i++)
		p_new[i] = p[i-1];
	*/

	int k = 0;
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

void Deletete_element_by_index(int*& p, int &size, int index) {
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

bool Is_Simple_number(int n)
{
    if (n < 2) return false;
    for (int i = 2; i * 2 <= n; i++)
    {
        if (n % i == 0) return false;
    }
    return true;
}

/*
void Print_Simple_numbers(int n)
{
    for (int i = 2; i <= n; i++)
    {
        if (Is_Simple_number(i))
        {
            cout << i << " ";
        }
    }
    cout << endl;
}
*/

void Delete_Simple_numbers(int*& p, int& size)
{
    int* p_new = new int[size];
    int new_size = 0;

    for (int i = 0; i < size; i++)
    {
        if (!Is_Simple_number(p[i]))
        {
            p_new[new_size++] = p[i];
        }
    }

    Free(p);
    p = p_new;
    size = new_size;
}

void SeparateElements(int*& p, int size,
                      int*& neg, int& neg_size,
                      int*& pos, int& pos_size,
                      int*& zero, int& zero_size)
{
    neg_size = 0;
    pos_size = 0;
    zero_size = 0;

    for (int i = 0; i < size; i++)
    {
        if (p[i] < 0)
            neg_size++;
        else if (p[i] > 0)
            pos_size++;
        else
            zero_size++;
    }

    neg = new int[neg_size];
    pos = new int[pos_size];
    zero = new int[zero_size];

    neg_size = 0;
    pos_size = 0;
    zero_size = 0;

    for (int i = 0; i < size; i++)
    {
        if (p[i] < 0)
            neg[neg_size++] = p[i];
        else if (p[i] > 0)
            pos[pos_size++] = p[i];
        else
            zero[zero_size++] = p[i];
    }
}

int main()
{
    srand(time(NULL));

    int size = 25;
    int* p = Allocate(size);
    Init(p, size);
    cout << "Array before deletion of simple numbers: ";
    Print(p, size);
    Delete_Simple_numbers(p, size);
    cout << endl;

    cout << "Array after deletion of simple numbers: ";
    Print(p, size);
    cout << endl;

    int* neg = nullptr;
    int neg_size = 0;
    int* pos = nullptr;
    int pos_size = 0;
    int* zero = nullptr;
    int zero_size = 0;

    SeparateElements(p, size, neg, neg_size, pos, pos_size, zero, zero_size);
    cout << "Negative elements: ";
    Print(neg, neg_size);

    cout << "Positive elements: ";
    Print(pos, pos_size);

    cout << "Zero elements: ";
    Print(zero, zero_size);

    Free(neg);
    Free(pos);
    Free(zero);
    Free(p);

    return 0;
}