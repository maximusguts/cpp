#include <iostream>
#include <string>
using namespace std;

class Overcoat {
private:
    string type;   // Type of clothing (e.g., "Coat", "Jacket")
    double price;  // Price of the clothing

public:
    // Constructors
    Overcoat() : type("Unknown"), price(0.0) {}
    Overcoat(const string& t, double p) : type(t), price(p) {}

    // Assignment operator (=)
    Overcoat& operator=(const Overcoat& other) {
        if (this != &other) {        // Prevent self-assignment
            type = other.type;
            price = other.price;
        }
        return *this;                // Return reference to allow chain assignment (a = b = c)
    }

    // Equality operator (==)
    bool operator==(const Overcoat& other) const {
        return type == other.type;   // Two coats are "equal" if they have the same type
    }

    // Greater-than operator (>)
    bool operator>(const Overcoat& other) const {
        if (*this == other)          // Compare prices only if types are the same
            return price > other.price;
        else
            return false;            // Different types cannot be compared
    }

    // Less-than operator (<)
    bool operator<(const Overcoat& other) const {
        if (*this == other)          // Compare prices only if types are the same
            return price < other.price;
        else
            return false;            // Different types cannot be compared
    }

    // Print information about the coat
    void print() {
        cout << "Type: " << type << ", Price: " << price << endl;
    }
};

// Testing the Overcoat class
int main() {
    Overcoat coat1("Coat", 2500);
    Overcoat coat2("Coat", 3000);
    Overcoat coat3("Jacket", 1500);

    cout << "coat1 == coat2: " << (coat1 == coat2 ? "Yes" : "No") << endl;
    cout << "coat2 > coat1: " << (coat2 > coat1 ? "Yes" : "No") << endl;
    cout << "coat3 > coat1: " << (coat3 > coat1 ? "Yes" : "No") << endl;

    cout << "coat2 < coat1: " << (coat2 < coat1 ? "Yes" : "No") << endl;
    cout << "coat3 < coat1: " << (coat3 < coat1 ? "Yes" : "No") << endl;

    coat1 = coat3;  // Test assignment operator
    cout << "\nAfter coat1 = coat3:\n";
    coat1.print();

    return 0;
}
