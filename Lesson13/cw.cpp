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

// ***************************************************************

int My_strlen(const char* str)
{
	int counter = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		counter++;
	}

	return counter;
}

void My_strcpy(char* str2, const char* str1)
{
	int i;
	for (i = 0; str1[i] != '\0'; i++)
	{
		str2[i] = str1[i];
	}
	str2[i] = '\0';
}

void My_strcat(char* str1, char* str2)
{
	char* p = str1;
	while (*p != '\0')
	{
		p++;
	}
	
	int i;
	for (i = 0; str2[i] != '\0'; i++)
	{
		p[i] = str2[i];  
	}
	p[i] = '\0';
}

void replace_spacetab(char* str)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ' ')
			str[i] == '\t';
	}
}

int countWords(const char* str)
{
	int counter = 0;

	for (int i = 0; str[i] != '\0'; i++)
	{
		if((str[i] != ' ')   and   ((str[i-1] == ' ') or (i==0)))
		counter++;
	}

	return counter;
}

// ***************************************************************

void reverse(char* str)
{
    int len = My_strlen(str);
    for (int i = 0; i < len / 2; i++)
    {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void set_upr(char* str) {
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
    }
}

void set_lwr(char* str) {
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
    }
}

int main()
{
    srand(time(NULL));
    
    Print("Enter any text: ");
    char str[100];
    cin.getline(str, 100);
    Print("Your text: ");
    Print(str);
    Print("Length of your text: ");
    Print(My_strlen(str));
    Print("Reversed text: ");
    reverse(str);
    Print(str);

    return 0;
}