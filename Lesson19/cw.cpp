#include <iostream>
#include <iomanip>
#include <cstring>  // для memset
#include <cstdlib>  // для system("cls")
#include "io.h"

using namespace std;

// Структури
struct Student {
    double GPA;
    int age;
    char name[29];
    char surname[29];
    char phone[18];
};

struct ArrayStudents {
    Student** ptrSt;  // масив вказівників на студентів
    int Size;
    int Count;
    int Block;
};

// Глобальна змінна
ArrayStudents as = {nullptr, 0, 0, 10};

// --- Функції ---

void Menu(char menu[][50], int row) {
    for (int i = 0; i < row; i++)
        cout << menu[i] << endl;
}

void InputData(Student* student) {
    cout << "Name:" << endl;
    cin >> student->name;
    cout << "Surname:" << endl;
    cin >> student->surname;
    cout << "Age:" << endl;
    cin >> student->age;
    cout << "Phone:" << endl;
    cin >> student->phone;
    cout << "GPA:" << endl;
    cin >> student->GPA;
}

void ClearFile() {
    FILE* f = nullptr;
    fopen_s(&f, "students.txt", "wb");  // відкриваємо файл для запису, що очищує його
    fclose(f);
}

void FillFile(ArrayStudents& as) {
    ClearFile();

    FILE* f = nullptr;
    fopen_s(&f, "students.txt", "ab");

    if (as.Count == 0) {
        fclose(f);
        return; // файл порожній
    }

    for (int i = 0; i < as.Count; i++) {
        fwrite(as.ptrSt[i], sizeof(Student), 1, f);
    }

    fclose(f);
}

void AddStudents(ArrayStudents& as) {
    system("cls");

    int count;
    cout << "How many? " << endl;
    cin >> count;
    if (count <= 0)
        return;

    FILE* f = nullptr;
 
	fopen_s(&f, "students.txt", "ab");

    int new_count = as.Count + count;
    if (as.Size < new_count) {
        as.Size = new_count + as.Block - (new_count % as.Block);
        Student** temp = new Student*[as.Size];
        for (int i = 0; i < as.Count; i++) {
            temp[i] = as.ptrSt[i];
        }
        delete[] as.ptrSt;
        as.ptrSt = temp;
    }

    for (int i = 0; i < count; i++) {
        Student* st = new Student;
        cout << "Enter the data:" << endl;
        InputData(st);
        as.ptrSt[as.Count] = st;
        as.Count++;
        fwrite(st, sizeof(Student), 1, f);
    }

    cout << "+ Students added successfully." << endl;
    fclose(f);
    system("pause");
}

void DeleteStudent(ArrayStudents& as)
{
    system("cls");

    int delete_all_acepted;
    cout << "Do you want to delete all students? (1 - Yes, 0 - No): ";
    cin >> delete_all_acepted;

    if (delete_all_acepted == 1) {
        ClearFile();
        for (int i = 0; i < as.Count; i++) {
            delete as.ptrSt[i];
        }
        delete[] as.ptrSt;
        as.ptrSt = nullptr;
        as.Count = 0;
        as.Size = 0;
        cout << "All students deleted." << endl;
        system("pause");
        return;
    }

    int index;
    cout << "Enter the index of the student to delete (0 to " << as.Count - 1 << "): ";
    cin >> index;

    if (index < 0 || index >= as.Count) {
        cout << "Invalid index!" << endl;
        system("pause");
        return;
    }

    FILE* f = nullptr;

    fopen_s(&f, "students.txt", "wb");
    fclose(f);

    fopen_s(&f, "students.txt", "ab");

    int new_count = as.Count - 1;
    Student** new_ptrSt = new Student*[new_count];
    int k = 0;
    for (int i = 0; i < as.Count; i++) {
        if (i != index) {
            new_ptrSt[i - k] = as.ptrSt[i];
            fwrite(as.ptrSt[i], sizeof(Student), 1, f);
        } else {
            delete as.ptrSt[i];
            k++;
        }
    }
    fclose(f);
    as.Count = new_count;
    delete[] as.ptrSt;
    as.ptrSt = new_ptrSt;
    system("pause");
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

// char* Int_to_str(int num)
// {
//     int length = 0;
//     int temp = num;
//     if (num < 0) {
//         length++; // for negative sign
//         temp = -temp; // make positive for length calculation
//     }
    
//     do {
//         length++;
//         temp /= 10;
//     } while (temp != 0);

//     char* str = new char[length + 1]; // +1 for null terminator
//     str[length] = '\0'; // null-terminate the string

//     int is_negative = 0;

//     if (num < 0) {
//         str[0] = '-';
//         num = -num; // make positive for conversion
//         is_negative = 1;
//     }

//     for (int i = length - 1; i >= (is_negative == 1 ? 1 : 0); i--) {
//         str[i] = (num % 10) + '0'; // convert digit to character
//         num /= 10;
//     }

//     return str;
// }

void Search_str(Student** list, int n, char* name_type)
{
    system("cls");
    if (strcmp(name_type, "Name") == 0) {
        char input_str[100];
        cout << "Enter name to search: ";
        cin.ignore();
        cin.getline(input_str, 100);

        ToLower(input_str); // convert input to lowercase

        if (n == 0) {
            cout << "No data to search." << endl;
            system("pause");
            return;
        }

        bool found = false;
        for (int i = 0; i < n; i++)
        {
            char* lower_name = new char[strlen(list[i]->name) + 1];
            Strcpy(lower_name, list[i]->name);
            ToLower(lower_name); // convert each name to lowercase

            int match_index = Strstr_index(lower_name, input_str);
            if (match_index >= 0) {
                char template_output[200] = "";
                Strncat(template_output, list[i]->name, match_index);
                Strcat(template_output, "\"");
                Strncat(template_output, list[i]->name + match_index, strlen(input_str));
                Strcat(template_output, "\"");
                Strcat(template_output, list[i]->name + match_index + strlen(input_str));
                cout << "Found: " << template_output << endl
                     << "    At the position: " << i + 1 << endl << endl;
                found = true;
            }
            delete[] lower_name; // free the temporary string
        }
        
        if (!found) {
            cout << "No matching students found." << endl;
        }
        system("pause");
        return;
    } else if (strcmp(name_type, "Surname") == 0) {
        system("cls");
        char input_surname[100];
        cout << "Enter surname to search: ";
        cin.ignore();
        cin.getline(input_surname, 100);
        ToLower(input_surname); // convert input to lowercase
        if (n == 0) {
            cout << "No data to search." << endl;
            system("pause");
            return;
        }
        bool found_surname = false;
        for (int i = 0; i < n; i++)
        {
            char* lower_surname = new char[strlen(list[i]->surname) + 1];
            Strcpy(lower_surname, list[i]->surname);
            ToLower(lower_surname); // convert each surname to lowercase

            int match_index = Strstr_index(lower_surname, input_surname);
            if (match_index >= 0) {
                char template_output[200] = "";
                Strncat(template_output, list[i]->surname, match_index);
                Strcat(template_output, "\"");
                Strncat(template_output, list[i]->surname + match_index, strlen(input_surname));
                Strcat(template_output, "\"");
                Strcat(template_output, list[i]->surname + match_index + strlen(input_surname));
                cout << "Found: " << template_output << endl
                     << "    At the position: " << i + 1 << endl << endl;
                found_surname = true;
            }
            delete[] lower_surname; // free the temporary string
        }
        system("pause");
        return;
    }
}

void Search_int(Student** list, int n, char* num_type)
{
    system("cls");
    if (strcmp(num_type, "Age") == 0) {
        int input_age;
        cout << "Enter age to search: ";
        cin >> input_age;

        if (n == 0) {
            cout << "No data to search." << endl;
            system("pause");
            return;
        }

        bool found = false;
        for (int i = 0; i < n; i++)
        {
            if (list[i]->age == input_age) {
                cout << "Found: " << list[i]->name << " " << list[i]->surname
                     << ", Age: " << list[i]->age << endl
                     << "    At the position: " << i + 1 << endl << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No matching students found." << endl;
        }
        system("pause");
        return;
    } else if (strcmp(num_type, "Phone") == 0) {
        system("cls");
        char input_phone[100];
        cout << "Enter phone to search: ";
        cin.ignore();
        cin.getline(input_phone, 100);
        ToLower(input_phone); // convert input to lowercase
        if (n == 0) {
            cout << "No data to search." << endl;
            system("pause");
            return;
        }
        bool found_phone = false;
        for (int i = 0; i < n; i++)
        {
            char* phone = new char[strlen(list[i]->phone) + 1];
            Strcpy(phone, list[i]->phone);

            int match_index = Strstr_index(phone, input_phone);
            if (match_index >= 0) {
                char template_output[200] = "";
                Strncat(template_output, phone, match_index);
                Strcat(template_output, "\"");
                Strncat(template_output, phone + match_index, strlen(input_phone));
                Strcat(template_output, "\"");
                Strcat(template_output, phone + match_index + strlen(input_phone));
                cout << "Found: " << list[i]->name << " " << list[i]->surname
                     << ", Phone: " << template_output << endl
                     << "    At the position: " << i + 1 << endl << endl;
                found_phone = true;
            }
            delete[] phone; // free the temporary string
        }
        system("pause");
        return;
    }
}

void Search(ArrayStudents& as) {
    system("cls");
    cout << "according to what data do you want to search?" << endl;
    cout << "1. Name" << endl;
    cout << "2. Surname" << endl;
    cout << "3. Age" << endl;
    cout << "4. Phone" << endl;

    int choice;
    cin >> choice;

    switch (choice) {
        case 1: {
        Search_str(as.ptrSt, as.Count, "Name");
        return;
        }
        case 2: {
        Search_str(as.ptrSt, as.Count, "Surname");
        return;
        }
        case 3: {
        Search_int(as.ptrSt, as.Count, "Age");
        return;
        }
        case 4: {
        Search_int(as.ptrSt, as.Count, "Phone");
        return;
        }
        default: {
            system("cls");
            cout << "Invalid choice!" << endl;
            system("pause");
            return;
        }
    }
}

void Print(ArrayStudents& as) {
    system("cls");
    cout << setw(3) << "#" << setw(30) << "Name" << setw(30) << "Surname"
         << setw(5) << "Age" << setw(20) << "Phone" << setw(10) << "GPA" << endl;

    for (int i = 0; i < as.Count; i++) {
        cout << setw(3) << i + 1
             << setw(30) << as.ptrSt[i]->name
             << setw(30) << as.ptrSt[i]->surname
             << setw(5) << as.ptrSt[i]->age
             << setw(20) << as.ptrSt[i]->phone
             << setw(10) << as.ptrSt[i]->GPA << endl;
    }

    system("pause");
}

void Sort(ArrayStudents& as) {
    system("cls");
    if (as.Count == 0) {
        cout << "No students to sort." << endl;
        system("pause");
        return;
    }

    FILE* f = nullptr;

    fopen_s(&f, "students.txt", "wb");
    fclose(f);

    fopen_s(&f, "students.txt", "ab");

    for (int i = 0; i < as.Count - 1; i++) {
        for (int j = 0; j < as.Count - 1 - i; j++) {
            if (strcmp(as.ptrSt[j]->name, as.ptrSt[j + 1]->name) > 0) {
                // Swap pointers
                Student* temp = as.ptrSt[j];
                as.ptrSt[j] = as.ptrSt[j + 1];
                as.ptrSt[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < as.Count; i++) {
        fwrite(as.ptrSt[i], sizeof(Student), 1, f);
    }

    cout << "Students sorted by name." << endl;
    fclose(f);
    system("pause");
    return;
}

void EditStudent(ArrayStudents& as) {
    system("cls");
    int index;
    cout << "Enter the index of the student to edit (0 to " << as.Count - 1 << "): ";
    cin >> index;

    FILE* f = nullptr;

    fopen_s(&f, "students.txt", "wb");
    fclose(f);

    fopen_s(&f, "students.txt", "ab");

    if (index < 0 || index >= as.Count) {
        cout << "Invalid index!" << endl;
        system("pause");
        return;
    }
    cout << "Current data: " << as.ptrSt[index]->name << " "
         << as.ptrSt[index]->surname << ", Age: " << as.ptrSt[index]->age
         << ", Phone: " << as.ptrSt[index]->phone
         << ", GPA: " << as.ptrSt[index]->GPA << endl;

    cout << "Enter new data:" << endl;
    InputData(as.ptrSt[index]);

    for (int i = 0; i < as.Count; i++) {
        fwrite(as.ptrSt[i], sizeof(Student), 1, f);
    }

    cout << "Student data updated." << endl;
    fclose(f);
    system("pause");
    return;
}

void Destroy(ArrayStudents& as) {
    for (int i = 0; i < as.Count; i++) {
        delete as.ptrSt[i];
    }
    delete[] as.ptrSt;
    memset(&as, 0, sizeof(ArrayStudents));
}

// --- Основна функція ---
int main() {
    srand(time(NULL));

    FILE* f = nullptr;
    fopen_s(&f, "students.txt", "ab");  // створюємо файл в разі першого запуску
    fclose(f);

    fopen_s(&f, "students.txt", "rb");  // відкриваємо файл на читання
    int length = _filelength((_fileno(f))); // довжина файла в бт
    length = length / sizeof(Student);  // кількість студентів в базі з файла

    if (length != 0)
    {
        as.Count = length;
        as.Size = as.Count + as.Block;

        if (as.ptrSt != nullptr) {
            for (int i = 0; i < as.Count; ++i) {
                delete as.ptrSt[i];
            }
            delete[] as.ptrSt;
        }

        Student** temp = new Student * [length];
        as.ptrSt = temp;
 
        for (int i = 0; i < length; i++)  // вичитка даних в масив студентів із файла
        {
            Student* student = new Student;
            fread(student, sizeof(Student), 1, f);
            as.ptrSt[i] = student;
        }
 
    }
    else
    {
        as.ptrSt = nullptr;
        as.Size = 0;
        as.Count = 0;
    }
 
    fclose(f);

    char menu[9][50] = {
        "1. Add students",
        "2. Delete",
        "3. Search",
        "4. Print",
        "5. Sort",
        "6. Edit",
        "7. Clear file",
        "8. Fill file",
        "9. Exit"
    };

    while (true) {
        system("cls");
        Menu(menu, 9);

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            AddStudents(as);
            break;
        case 2:
            DeleteStudent(as);
            break;
        case 3:
            Search(as);
            break;
        case 4:
            Print(as);
            break;
        case 5:
            Sort(as);
            break;
        case 6:
            EditStudent(as);
            break;
        case 7:
            system("cls");
            ClearFile();
            cout << "File cleared." << endl;
            system("pause");
            break;
        case 8:
            system("cls");
            FillFile(as);
            cout << "File filled with current data." << endl;
            system("pause");
            break;
        case 9:
            Destroy(as);
            system("cls");
            return 0;
        default:
            cout << "Error" << endl;
            system("pause");
        }
    }

    return 0;
}
