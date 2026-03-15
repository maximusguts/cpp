#include <iostream>
#include <cstring>  // для strcpy, strlen

using namespace std;

class String {
private:
    char* str;                 // pointer to array of characters
    size_t length;             // string lengh
    static int objectCount;    // static object counter

public:
    // Default constructor
    String() : String(80) {}

    // Constructor with arbitrary lengh
    String(size_t size) {
        length = size;
        str = new char[length + 1];
        str[0] = '\0'; // emphty string
        objectCount++;
    }

    // Constructor with initialization user's string
    String(const char* input) : String(strlen(input)) {
        strcpy(str, input);
    }

    // Copy constructor (deep copy)
    String(const String& other) : String(other.length) {
        strcpy(str, other.str);
        cout << "[Copy constructor called]\n";
    }

    // Move constructor
    String(String&& other) {
        // "Steal" the resource
        str = other.str;
        length = other.length;
        
        // Nullify the source
        other.str = nullptr;
        other.length = 0;

        objectCount++;
        cout << "[Move constructor called]\n";
    }

    // Destructor
    ~String() {
        delete[] str;
        objectCount--;
    }

    // Keyboard input method
    void input() {
        std::cout << "Enter string: ";
        std::cin.getline(str, length + 1);
    }

    // Screen display method
    void print() const {
        std::cout << str << std::endl;
    }

    // Static function for object count
    static int getObjectCount() {
        return objectCount;
    }
};

// Initialization of static class member
int String::objectCount = 0;

// Use example
int main() {
    // String s1;                     // creating string with 80 characters
    // String s2(50);                 // creating string with 50 characters
    // String s3("Hello, world");    // creating string with some text

    // std::cout << "Current number of objects: " << String::getObjectCount() << std::endl;

    // s1.input();
    // s1.print();
    // s3.print();

    // std::cout << "Number of objects after work: " << String::getObjectCount() << std::endl;

    cout << "Creating s1...\n";
    String s1("Hello");

    cout << "\nCopying s1 to s2...\n";
    String s2 = s1;  // Copy constructor

    cout << "\nMoving s1 to s3...\n";
    String s3 = move(s1);  // Move constructor

    cout << "\n--- Object contents ---\n";
    cout << "s2: "; s2.print();
    cout << "s3: "; s3.print();

    cout << "\nTotal objects alive: " << String::getObjectCount() << endl;

    return 0;
}
