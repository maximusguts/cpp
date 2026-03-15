#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <cstring>

using namespace std;

void Menu(char menu[][50], int row)
{
	for (int i = 0; i < row; i++)
		cout << menu[i] << endl;
}

char** AddStudent(char** old_list, int& old_n)
{
	system("cls");
	int count;
	cout << "How many? " << endl;
	cin >> count;
	cin.get();

	int new_n = old_n + count;
	char** new_list = new char* [new_n];

	for (int i = 0; i < old_n; i++)
		new_list[i] = old_list[i];

	char str[100];

	for (int i = old_n; i < new_n; i++)
	{
		cout << i << " Enter data: ";
		cin.getline(str, 100);

		int length = strlen(str) + 1;
		new_list[i] = new char[length];
		strcpy_s(new_list[i], length, str);
	}

	old_n = new_n;
	delete[] old_list;

	return new_list;
}

void Print(char** list, int n)
{
	system("cls");
	cout << "count of students: "<< n << endl;

	for (int i = 0; i < n; i++)
		cout << i+1 << ". " << list[i] << endl;

	cout << endl;
	system("pause");
}

void FindStudent(char** list, int n) {
	system("cls");
	int index;
	cout << "Enter student number (0 to " << n - 1 << "): ";
	cin >> index;

	if (index >= 0 && index < n) {
		cout << "Student at position " << index << ": " << list[index] << endl;
	}
	else {
		cout << "Invalid student number!" << endl;
	}

	system("pause");
}

void EditStudent(char** list, int n) {
	system("cls");
	int index;
	cout << "Enter student number to edit (0 to " << n - 1 << "): ";
	cin >> index;
	cin.ignore();

	if (index < 0 || index >= n) {
		cout << "Invalid index!" << endl;
		return;
	}

	cout << "Current data: " << list[index] << endl;

	char buffer[100];
	cout << "Enter new data: ";
	cin.getline(buffer, 100);

	int newLength = strlen(buffer) + 1;
	char* newData = new char[newLength];
	strcpy_s(newData, newLength, buffer);

	delete[] list[index];
	list[index] = newData;

	cout << "Student data updated." << endl;
	system("pause");
}

void SortStudents(char** list, int n) {
	system("cls");
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			if (strcmp(list[j], list[j + 1]) > 0) {
				char* temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}

	cout << "List sorted alphabetically (case-sensitive)." << endl;
	system("pause");
}

int main()
{
	char** list_students = nullptr;
	char menu[7][50] =
	{
		"1. Add students",
		"2. Delete ",
		"3. Search ",
		"4. Print",
		"5. Sort",
		"6. Edit",
		"7. Exit",
	};

	int n = 0;

	while (true)
	{
		system("cls");
		Menu(menu, 7);
		int choice = _getch();

		switch (choice)
		{
		case '1':
			list_students = AddStudent(list_students, n);
			break;
		case '2':
			// Optionally implement deletion
			break;
		case '3':
			FindStudent(list_students, n);
			break;
		case '4':
			Print(list_students, n);
			break;
		case '5':
			SortStudents(list_students, n);
			break;
		case '6':
			EditStudent(list_students, n);
			break;
		case '7':
			return 0;
		}
	}

	return 0;
}
