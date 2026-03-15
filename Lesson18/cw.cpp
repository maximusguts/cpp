#include <iostream>
#include <cstring>   // для strcmp
#include <cstdio>    // для FILE, fopen_s, fclose, fread, fwrite, fgets, fputs

using namespace std;

// Структура студента
struct Student {
    char name[29];
    char surname[29];
};

// Структура масиву студентів
struct ArrayStudents {
    Student** ptrSt = nullptr;
    int Count = 0;
};

// Функція видалення студента
void DeleteStudent(ArrayStudents& as) {
    system("cls");

    char name[29], surname[29];

    cout << "Name" << endl;
    cin >> name;
    cout << "Surname" << endl;
    cin >> surname;

    for (int i = 0; i < as.Count; i++) {
        if ((!strcmp(name, as.ptrSt[i]->name)) && (!strcmp(surname, as.ptrSt[i]->surname))) {
            delete as.ptrSt[i];

            for (int j = i; j < as.Count - 1; j++) {
                as.ptrSt[j] = as.ptrSt[j + 1];
            }

            as.Count--;

            as.ptrSt[as.Count] = nullptr;

            cout << "+" << endl;
            system("pause");
            return;
        }
    }

    cout << "not found" << endl;
    system("pause");
}

int main() {
    char filename[255];

    cout << "Path:" << endl; // відносний або абсолютний шлях до файла
    cin.getline(filename, 255);

    // файловий вказівник
    FILE* f = nullptr;

    // відкриття файла
    fopen_s(&f, filename, "ab");  // rb-read   wb-write   ab-append(дозапис)
    // b - бінарний режим

    int i = 5;
    double d = 40.5;
    bool b = true;

    // fwrite  та fread
    fwrite(&i, sizeof(int), 1, f);
    fwrite(&d, sizeof(double), 1, f);
    fwrite(&b, sizeof(bool), 1, f);

    fclose(f);

    int i2;
    // int i3;
    // int i4;
    double d2;
    bool b2;

    fopen_s(&f, filename, "rb");

    fread(&i2, sizeof(int), 1, f);
    // fread(&i3, sizeof(int), 1, f);
    // fread(&i4, sizeof(int), 1, f);
    fread(&d2, sizeof(double), 1, f);
    fread(&b2, sizeof(bool), 1, f);

    cout << i2 << "   " << d2 << "   " << b2 << endl;
    // cout << i2 << "   " << i3 << "   " << i4 << endl;

    fclose(f);

    return 0;
}
