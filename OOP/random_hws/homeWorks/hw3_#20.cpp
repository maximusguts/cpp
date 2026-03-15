#include <iostream>
#include <fstream>
#include <string>
#include <bitset> // For binary output

using namespace std;

// === Base Class ===
class FileHandler {
public:
    // Virtual function as required by the task
    virtual void Display(const char* path) {
        ifstream file(path);
        if (!file.is_open()) {
            cout << "[Base] Error: Cannot open file " << path << endl;
            return;
        }

        cout << "--- Base Class Output (Text) ---" << endl;
        char ch;
        // Read file char by char and print it
        while (file.get(ch)) {
            cout << ch;
        }
        cout << "\n--------------------------------" << endl;
        file.close();
    }

    // Virtual destructor is important for polymorphism
    virtual ~FileHandler() {}
};

// === Derived Class 1: ASCII Codes ===
class AsciiFileHandler : public FileHandler {
public:
    void Display(const char* path) override {
        ifstream file(path);
        if (!file.is_open()) {
            cout << "[ASCII] Error: Cannot open file " << path << endl;
            return;
        }

        cout << "--- Derived Class 1 Output (ASCII Codes) ---" << endl;
        char ch;
        while (file.get(ch)) {
            // Cast char to int to display ASCII code
            cout << static_cast<int>(ch) << " ";
        }
        cout << "\n--------------------------------------------" << endl;
        file.close();
    }
};

// === Derived Class 2: Binary Output ===
class BinaryFileHandler : public FileHandler {
public:
    void Display(const char* path) override {
        ifstream file(path);
        if (!file.is_open()) {
            cout << "[Binary] Error: Cannot open file " << path << endl;
            return;
        }

        cout << "--- Derived Class 2 Output (Binary) ---" << endl;
        char ch;
        while (file.get(ch)) {
            // bitset<8> converts the char to 8 bits
            cout << bitset<8>(ch) << " ";
        }
        cout << "\n---------------------------------------" << endl;
        file.close();
    }
};

int main() {
    // 1. Create a dummy file for testing purposes
    const char* filename = "test_file.txt";
    ofstream tempFile(filename);
    tempFile << "Hi C++"; // Simple text content
    tempFile.close();

    // 2. Polymorphism demonstration
    // We use a pointer to the Base class to store Derived objects
    FileHandler* handler = nullptr;

    // --- Test Base Class ---
    handler = new FileHandler();
    handler->Display(filename);
    delete handler; 

    cout << endl;

    // --- Test ASCII Handler ---
    handler = new AsciiFileHandler();
    handler->Display(filename);
    delete handler;

    cout << endl;

    // --- Test Binary Handler ---
    handler = new BinaryFileHandler();
    handler->Display(filename);
    delete handler;

    return 0;
}
