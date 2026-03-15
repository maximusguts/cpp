#include <iostream> // для cout, cin
#include <iomanip>  // для setw
#include <cstring>  // для memset
#include <cstdlib>  // для system("cls")
#include "io.h"     // для _filelength, _fileno

using namespace std;

// Структури
struct Book {
    int year;
    int pages;
    char title[100];
    char author[100];
    char genre[50];
};

struct ArrayBooks {
    Book** ptrBk;  // масив вказівників на студентів
    int Size;
    int Count;
    int Block;
};

// Глобальна змінна
ArrayBooks ab = {nullptr, 0, 0, 10};

// --- Функції ---

void Menu(char menu[][50], int row) {
    for (int i = 0; i < row; i++)
        cout << menu[i] << endl;
}

void InputData(Book* books) {
    cout << "title:" << endl;
    cin.ignore();
    cin.getline(books->title, 100);
    cout << "author:" << endl;
    cin.ignore();
    cin.getline(books->author, 100);
    cout << "year:" << endl;
    cin >> books->year;
    cout << "genre:" << endl;
    cin.ignore();
    cin.getline(books->genre, 100);
    cout << "pages:" << endl;
    cin >> books->pages;
}

void ClearFile() {
    FILE* f = nullptr;
    fopen_s(&f, "books.txt", "wb");  // відкриваємо файл для запису, що очищує його
    fclose(f);
}

void FillFile(ArrayBooks& ab) {
    ClearFile();

    FILE* f = nullptr;
    fopen_s(&f, "books.txt", "ab");

    if (ab.Count == 0) {
        fclose(f);
        return; // файл порожній
    }

    for (int i = 0; i < ab.Count; i++) {
        fwrite(ab.ptrBk[i], sizeof(Book), 1, f);
    }

    fclose(f);
}

void AddBooks(ArrayBooks& ab) {
    system("cls");

    int count;
    cout << "How many? " << endl;
    cin >> count;
    if (count <= 0)
        return;

    FILE* f = nullptr;
 
	fopen_s(&f, "books.txt", "ab");

    int new_count = ab.Count + count;
    if (ab.Size < new_count) {
        ab.Size = new_count + ab.Block - (new_count % ab.Block);
        Book** temp = new Book*[ab.Size];
        for (int i = 0; i < ab.Count; i++) {
            temp[i] = ab.ptrBk[i];
        }
        delete[] ab.ptrBk;
        ab.ptrBk = temp;
    }

    for (int i = 0; i < count; i++) {
        Book* st = new Book;
        cout << "Enter the data:" << endl;
        InputData(st);
        ab.ptrBk[ab.Count] = st;
        ab.Count++;
        fwrite(st, sizeof(Book), 1, f);
    }

    cout << "+ Books added successfully." << endl;
    fclose(f);
    system("pause");
}

void DeleteBook(ArrayBooks& ab)
{
    system("cls");

    if (ab.Count == 0) {
        cout << "No books to delete." << endl;
        system("pause");
        return;
    }

    int index;
    cout << "Enter the index of the book to delete (1 to " << ab.Count
         << "). \n And if you want delete all books, enter a \"0\": ";
    cin >> index;

    if (index == 0) {
        ClearFile();
        for (int i = 0; i < ab.Count; i++) {
            delete ab.ptrBk[i];
        }
        delete[] ab.ptrBk;
        ab.ptrBk = nullptr;
        ab.Count = 0;
        ab.Size = 0;
        cout << "All books deleted." << endl;
        system("pause");
        return;
    }

    index--; // Зменшуємо на 1, щоб індекс був від 0 до Count-1

    if (index < 0 || index >= ab.Count) {
        cout << "Invalid index!" << endl;
        system("pause");
        return;
    }

    FILE* f = nullptr;

    fopen_s(&f, "books.txt", "wb");
    fclose(f);

    fopen_s(&f, "books.txt", "ab");

    int new_count = ab.Count - 1;
    Book** new_ptrBk = new Book*[new_count];
    int k = 0;
    for (int i = 0; i < ab.Count; i++) {
        if (i != index) {
            new_ptrBk[i - k] = ab.ptrBk[i];
            fwrite(ab.ptrBk[i], sizeof(Book), 1, f);
        } else {
            delete ab.ptrBk[i];
            k++;
        }
    }
    fclose(f);
    ab.Count = new_count;
    delete[] ab.ptrBk;
    ab.ptrBk = new_ptrBk;
    cout << "Book deleted successfully." << endl << endl;
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
    if (n < 0) {
        n = 0; // if n is negative, set it to 0
    } if (n > strlen(src)) {
        n = strlen(src); // if n is greater than src length, adjust it
    }

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

void Search_str(Book** list, int n, char* name_type)
{
    system("cls");
    if (strcmp(name_type, "Title") == 0) {
        char input_str[100];
        cout << "Enter title to search: ";
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
            char* lower_title = new char[strlen(list[i]->title) + 1];
            Strcpy(lower_title, list[i]->title);
            ToLower(lower_title); // convert each title to lowercase

            int match_index = Strstr_index(lower_title, input_str);
            if (match_index >= 0) {
                char template_output[200] = "";
                Strncat(template_output, list[i]->title, match_index);
                Strcat(template_output, "\"");
                Strncat(template_output, list[i]->title + match_index, strlen(input_str));
                Strcat(template_output, "\"");
                Strcat(template_output, list[i]->title + match_index + strlen(input_str));
                cout << "Found: " << template_output << endl << "    At the position: " << i + 1 << endl << endl;
                found = true;
            }
            delete[] lower_title; // free the temporary string
        }
        
        if (!found) {
            cout << "No matching books found." << endl;
        }
        system("pause");
        return;
    } else if (strcmp(name_type, "Author") == 0) {
        system("cls");
        char input_author[100];
        cout << "Enter author to search: ";
        cin.ignore();
        cin.getline(input_author, 100);
        ToLower(input_author); // convert input to lowercase
        if (n == 0) {
            cout << "No data to search." << endl;
            system("pause");
            return;
        }
        bool found_author = false;
        for (int i = 0; i < n; i++)
        {
            char* lower_author = new char[strlen(list[i]->author) + 1];
            Strcpy(lower_author, list[i]->author);
            ToLower(lower_author); // convert each author to lowercase

            int match_index = Strstr_index(lower_author, input_author);
            if (match_index >= 0) {
                char template_output[200] = "";
                Strncat(template_output, list[i]->author, match_index);
                Strcat(template_output, "\"");
                Strncat(template_output, list[i]->author + match_index, strlen(input_author));
                Strcat(template_output, "\"");
                Strcat(template_output, list[i]->author + match_index + strlen(input_author));
                cout << "Found: " << template_output << endl;
                found_author = true;
            }
            delete[] lower_author; // free the temporary string
        }
        system("pause");
        return;
    }
}

void Search(ArrayBooks& ab) {
    system("cls");
    cout << "according to what data do you want to search?" << endl;
    cout << "1. Title" << endl;
    cout << "2. Author" << endl;

    int choice;
    cin >> choice;

    switch (choice) {
        case 1: {
        Search_str(ab.ptrBk, ab.Count, "Title");
        return;
        }
        case 2: {
        Search_str(ab.ptrBk, ab.Count, "Author");
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

void Print(ArrayBooks& ab) {
    system("cls");
    cout << setw(3) << "#" << setw(30) << "Title" << setw(30) << "Author"
         << setw(7) << "Year" << setw(20) << "Genre" << setw(10) << "Pages" << endl;

    for (int i = 0; i < ab.Count; i++) {
        cout << setw(3) << i + 1
             << setw(30) << ab.ptrBk[i]->title
             << setw(30) << ab.ptrBk[i]->author
             << setw(7) << ab.ptrBk[i]->year
             << setw(20) << ab.ptrBk[i]->genre
             << setw(10) << ab.ptrBk[i]->pages << endl;
    }

    cout << endl;
    system("pause");
}

void Sort(ArrayBooks& ab) {
    system("cls");
    if (ab.Count == 0) {
        cout << "No books to sort." << endl;
        system("pause");
        return;
    }

    FILE* f = nullptr;

    fopen_s(&f, "books.txt", "wb");
    fclose(f);

    fopen_s(&f, "books.txt", "ab");

    // Bubble sort by year

    for (int i = 0; i < ab.Count - 1; i++) {
        for (int j = 0; j < ab.Count - 1 - i; j++) {
            if (ab.ptrBk[j]->year > ab.ptrBk[j + 1]->year) {
                // Swap pointers
                Book* temp = ab.ptrBk[j];
                ab.ptrBk[j] = ab.ptrBk[j + 1];
                ab.ptrBk[j + 1] = temp;
            }
        }
    }
    
    for (int i = 0; i < ab.Count; i++) {
        fwrite(ab.ptrBk[i], sizeof(Book), 1, f);
    }

    cout << "Books sorted by name." << endl;
    fclose(f);
    system("pause");
    return;
}

void EditBook(ArrayBooks& ab) {
    system("cls");
    int index;
    cout << "Enter the index of the book to edit (1 to " << ab.Count << "): ";
    cin >> index;
    index--; // Convert to 0-based index

    FILE* f = nullptr;

    fopen_s(&f, "books.txt", "wb");
    fclose(f);

    fopen_s(&f, "books.txt", "ab");

    if (index < 0 || index >= ab.Count) {
        cout << "Invalid index!" << endl;
        system("pause");
        return;
    }
    cout << "Current data: " << ab.ptrBk[index]->title << ", "
         << ab.ptrBk[index]->author << ", Year: " << ab.ptrBk[index]->year
         << ", Genre: " << ab.ptrBk[index]->genre
         << ", Pages: " << ab.ptrBk[index]->pages << endl;

    cout << "Enter new data:" << endl;
    InputData(ab.ptrBk[index]);

    for (int i = 0; i < ab.Count; i++) {
        fwrite(ab.ptrBk[i], sizeof(Book), 1, f);
    }

    cout << "Book data updated." << endl;
    fclose(f);
    system("pause");
    return;
}

void Destroy(ArrayBooks& ab) {
    for (int i = 0; i < ab.Count; i++) {
        delete ab.ptrBk[i];
    }
    delete[] ab.ptrBk;
    memset(&ab, 0, sizeof(ArrayBooks));
}

// --- Основна функція ---
int main() {
    srand(time(NULL));

    FILE* f = nullptr;
    fopen_s(&f, "books.txt", "ab");  // створюємо файл в разі першого запуску
    fclose(f);

    fopen_s(&f, "books.txt", "rb");  // відкриваємо файл на читання
    int length = _filelength((_fileno(f))); // довжина файла в бт
    length = length / sizeof(Book);  // кількість студентів в базі з файла

    if (length != 0)
    {
        ab.Count = length;
        ab.Size = ab.Count + ab.Block;
        
        if (ab.ptrBk != nullptr) {
            for (int i = 0; i < ab.Count; ++i) {
                delete ab.ptrBk[i]; // звільняємо попередні дані
            }
            delete[]ab.ptrBk;
        }

        Book** temp = new Book * [length];
        ab.ptrBk = temp;
 
        for (int i = 0; i < length; i++)  // вичитка даних в масив студентів із файла
        {
            Book* book = new Book;
            fread(book, sizeof(Book), 1, f);
            ab.ptrBk[i] = book;
        }
 
    }
    else
    {
        ab.ptrBk = nullptr;
        ab.Size = 0;
        ab.Count = 0;
    }
 
    fclose(f);

    char menu[9][50] = {
        "1. Add books",
        "2. Delete",
        "3. Search",
        "4. Print",
        "5. Sort",
        "6. Edit",
        "7. Clear file",
        "8. Fill file",
        "9. Exit"
    };

    char* AUTHOR_NAME = "Maxim Huts"; // <----- He is cool guy 😏

    system("cls");

    cout << "-----------------------" << endl;
    cout << "Book Management System\nBy " << AUTHOR_NAME << endl;
    cout << "-----------------------" << endl;
    cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << endl;
    cout << "////////////////////////" << endl;
    cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << endl;
    cout << "-----------------------" << endl;
    cout << "Current number of books: " << endl;
    cout << "           " << ab.Count << "          " << endl;
    cout << "-----------------------" << endl;
    cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << endl;
    cout << "////////////////////////" << endl;
    cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << endl;
    cout << "-----------------------" << endl;
    cout << "You can choose anyone\nof options:" << endl;
    cout << "-----------------------" << endl << endl;

    system("pause");

    while (true) {
        system("cls");

        cout << "Book Management System" << endl << endl;

        Menu(menu, 9);

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            AddBooks(ab);
            break;
        case 2:
            DeleteBook(ab);
            break;
        case 3:
            Search(ab);
            break;
        case 4:
            Print(ab);
            break;
        case 5:
            Sort(ab);
            break;
        case 6:
            EditBook(ab);
            break;
        case 7:
            system("cls");
            ClearFile();
            cout << "File cleared." << endl;
            system("pause");
            break;
        case 8:
            system("cls");
            FillFile(ab);
            cout << "File filled with current data." << endl;
            system("pause");
            break;
        case 9:
            Destroy(ab);
            system("cls");
            return 0;
        default:
            cout << "Error" << endl;
            system("pause");
        }
    }

    return 0;
}
