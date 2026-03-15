#include <iostream>
#include <cstdlib>
#include <string.h>
#include <conio.h>

using namespace std;

void Menu(char ptr[][50], int row)
{
	for (int i = 0; i < row; i++)
		cout << ptr[i] << endl;
}

char** AddStudent(char** list, int& n)
{
	int number;
	cout << "enter number: " << endl;
	cin >> number;
 
	cin.get();
 
	int old_n = n;
	int new_n = n + number;
 
	char** new_list = new char* [new_n];
 
	for (int i = 0; i < old_n; i++)
		new_list[i] = list[i];
 
	char str[100];
 
	for (int i = old_n; i < new_n; i++)
	{
		cout << "adding a studend with name:" << endl;
		cin.getline(str, 100);
 
		int len = strlen(str) + 1;
		new_list[i] = new char[len];
 
		//strcpy_s(new_list[i], len, str);
 
		 strcpy(new_list[i], str);   
 
	}
	n = new_n;
	delete[] list;
	return new_list;
}

char** DeleteStudent(char** list, int& n)
{
    int index;
    cout << "Enter the index of the student to delete (0 to " << n - 1 << "): ";
    cin >> index;
    cin.get();

    if (index < 0 || index >= n) {
        cout << "Invalid index!" << endl;
        return list;
    }

    char** new_list = new char*[n - 1];


    int k = 0;
    for (int i = 0; i < n; i++) {
        if (i != index) {
            new_list[i - k] = list[i];
        }
        else {
            delete[] list[i];
            k++;
        }
    }
    n--;
    delete[] list;
    return new_list;
}

void EditStudent(char** list, int n) {
    int index;
    cout << "Enter the index of the student to edit (0 to " << n - 1 << "): ";
    cin >> index;
    cin.get();

    if (index < 0 || index >= n) {
        cout << "Invalid index!" << endl;
        return;
    }

    char str[100];
    cout << "Enter new name for student at index " << index << ": ";
    cin.getline(str, 100);

    delete[] list[index];
    int len = strlen(str) + 1;
    list[index] = new char[len];
    strcpy(list[index], str);
    cout << "Student at index " << index << " has been updated." << endl;
}

void Print(char** list, int n)
{
	cout << "Students:" << endl << endl;
 
	for (int i = 0; i < n; i++)
		cout << i + 1 << ") " << list[i] << endl;

	cout << endl;
}

char** Sort(char** list, int n)
{
    // sorting by alphabetical order
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(list[i], list[j]) > 0) {
                char* temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
    cout << "Students sorted alphabetically." << endl;
    
    // #include <algorithm>
    // Alternatively, you can use std::sort with a custom comparator
    // std::sort(list, list + n, [](const char* a, const char* b) {
    //     return strcmp(a, b) < 0;
    // });
    // I didn't know that that is possible at all, but it is a good idea to use it.

    return list;
}

bool Strstr(char* str, char* sub_str)
{
    if (strlen(sub_str) > strlen(str))
        return false; // sub_str is longer than str

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == sub_str[0]) {
            for (int j = 0; sub_str[j] != '\0'; j++)
            {
                if (str[i + j] != sub_str[j]) {
                    break; // mismatch found
                }
                if (sub_str[j + 1] == '\0') {
                    return true; // found the substring
                }
            }
        }
    }
    return false;
}

int Strstr_index(char* str, char* sub_str)
{
    if (strlen(sub_str) > strlen(str))
        return -1; // sub_str is longer than str

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == sub_str[0]) {
            for (int j = 0; sub_str[j] != '\0'; j++)
            {
                if (str[i + j] != sub_str[j]) {
                    break; // mismatch found
                }
                if (sub_str[j + 1] == '\0') {
                    return i; // found the substring
                }
            }
        }
    }
    return -1; // substring not found
}

void ToLower(char* str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 32; // convert to lowercase
        }
    }
}

void Strcat(char* dest, const char* src)
{
    int dest_len = strlen(dest);
    int src_len = strlen(src);

    for (int i = 0; i < src_len; i++)
    {
        dest[dest_len + i] = src[i];
    }
    dest[dest_len + src_len] = '\0'; // null-terminate the destination string
}

void Strncat(char* dest, const char* src, int n)
{
    int dest_len = strlen(dest);
    for (int i = 0; i < n && src[i] != '\0'; i++)
    {
        dest[dest_len + i] = src[i];
    }
    dest[dest_len + n] = '\0'; // null-terminate the destination string
}

void Strcpy(char* dest, const char* src)
{
    int i = 0;
    do {
        dest[i] = src[i];
        i++;
    } while (src[i - 1] != '\0'); // copy until null terminator
    dest[i] = '\0'; // null-terminate the destination string
}

void Search(char** list, int n)
{
    char input_str[100];
    cout << "Enter name to search: ";
    cin.getline(input_str, 100);

    ToLower(input_str); // convert input to lowercase

    if (n == 0) {
        cout << "No students to search." << endl;
        return;
    }

    bool found = false;
    for (int i = 0; i < n; i++)
    {
        char* lower_name = new char[strlen(list[i]) + 1];
        Strcpy(lower_name, list[i]);
        ToLower(lower_name); // convert each name to lowercase

        int match_index = Strstr_index(lower_name, input_str);
        if (match_index >= 0) {
            char template_output[200] = "";
            Strncat(template_output, list[i], match_index);
            Strcat(template_output, "\"");
            Strncat(template_output, list[i] + match_index, strlen(input_str));
            Strcat(template_output, "\"");
            Strcat(template_output, list[i] + match_index + strlen(input_str));
            cout << "Found: " << template_output << endl;
            found = true;
        }
        delete[] lower_name; // free the temporary string
    }
    
    if (!found) {
        cout << "No matching students found." << endl;
    }
}

int main()
{
	char** list = nullptr;  
	char menu[][50] = {
	"1. +",
	"2. -",
	"3. edit",
	"4. print",
	"5. sort",
	"6. search",
	"7. exit",
	};
	int n = 0;  
 
	while (true)
	{
		Menu(menu, 7);
		char choice ;
		cin >> choice;
	    cin.get();
		switch (choice)
		{
		case '1':
			list = AddStudent(list, n);
			break;

		case '2':
			list = DeleteStudent(list, n);
            break;

		case '3':6
		    EditStudent(list, n);
			break;

		case '4':
			Print(list, n);
			break;

		case '5':
            list = Sort(list, n);
			break;

		case '6':
            Search(list, n);
			break;

		case '7':
			return 0;
		}
	}
}