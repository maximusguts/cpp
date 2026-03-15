#include <iostream>
#include <cstring>
#include <string>
using namespace std;

// Base class: String
class String {
protected:
    char* data;
public:
    // 1) Default constructor
    String() {
        data = new char[1];
        data[0] = '\0';
    }

    // 2) Constructor from C-string
    String(const char* s) {
        data = new char[strlen(s) + 1];
        strcpy(data, s);
    }

    // 3) Copy constructor
    String(const String& other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }

    // 4) Assignment operator
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] data;
            data = new char[strlen(other.data) + 1];
            strcpy(data, other.data);
        }
        return *this;
    }

    // 5) Length
    size_t length() const {
        return strlen(data);
    }

    // 6) Clear string
    void clear() {
        delete[] data;
        data = new char[1];
        data[0] = '\0';
    }

    // 7) Destructor
    virtual ~String() {
        delete[] data;
    }

    // 8) Concatenation
    String operator+(const String& other) const {
        char* newData = new char[length() + other.length() + 1];
        strcpy(newData, data);
        strcat(newData, other.data);
        String result(newData);
        delete[] newData;
        return result;
    }

    String& operator+=(const String& other) {
        char* newData = new char[length() + other.length() + 1];
        strcpy(newData, data);
        strcat(newData, other.data);
        delete[] data;
        data = newData;
        return *this;
    }

    // 9) Equality operators
    bool operator==(const String& other) const {
        return strcmp(data, other.data) == 0;
    }

    bool operator!=(const String& other) const {
        return !strcmp(data, other.data) == 0;
    }

    const char* c_str() const { return data; }
};

// Derived class: BitString
class BitString : public String {
private:
    bool isValid(const char* s) {
        for (size_t i = 0; i < strlen(s); ++i) {
            if (s[i] != '0' && s[i] != '1') return false;
        }
        return true;
    }

public:
    // 1) Default constructor
    BitString() : String() {}

    // 2) Constructor from C-string
    BitString(const char* s) {
        if (isValid(s)) {
            data = new char[strlen(s) + 1];
            strcpy(data, s);
        } else {
            data = new char[1];
            data[0] = '\0';
        }
    }

    // 3) Copy constructor
    BitString(const BitString& other) : String(other) {}

    // 4) Assignment operator
    BitString& operator=(const BitString& other) {
        String::operator=(other);
        return *this;
    }

    // 5) Destructor
    ~BitString() override = default;

    // 6) Change sign (two's complement)
    void changeSign() {
        for (size_t i = 0; i < length(); i++) {
            data[i] = (data[i] == '0') ? '1' : '0';
        }
        // Add 1 to the result (simplified)
        for (int i = length() - 1; i >= 0; i--) {
            if (data[i] == '0') {
                data[i] = '1';
                break;
            } else {
                data[i] = '0';
            }
        }
    }

    // 7) Add two bitstrings
    BitString operator+(const BitString& other) const {
        string a = data, b = other.data;
        string result = "";
        int carry = 0;
        int i = a.size() - 1, j = b.size() - 1;

        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) sum += a[i--] - '0';
            if (j >= 0) sum += b[j--] - '0';
            result = char(sum % 2 + '0') + result;
            carry = sum / 2;
        }

        return BitString(result.c_str());
    }

    BitString& operator+=(const BitString& other) {
        *this = *this + other;
        return *this;
    }

    // 8) Equality check inherited
};

// --- MAIN ---
int main() {
    BitString b1("1011");
    BitString b2("0010");
    BitString sum = b1 + b2;

    cout << "b1 = " << b1.c_str() << endl;
    cout << "b2 = " << b2.c_str() << endl;
    cout << "b1 + b2 = " << sum.c_str() << endl;

    b1.changeSign();
    cout << "After changeSign(b1): " << b1.c_str() << endl;

    return 0;
}
