#include <iostream>
using namespace std;

class Flat {
private:
    double area;   // Apartment area (in square meters)
    double price;  // Apartment price

public:
    // Default constructor
    Flat() : area(0.0), price(0.0) {}

    // Parameterized constructor
    Flat(double a, double p) : area(a), price(p) {}

    // Assignment operator (=)
    Flat& operator=(const Flat& other) {
        if (this != &other) {        // Prevent self-assignment
            area = other.area;
            price = other.price;
        }
        return *this;                // Return reference for chain assignment
    }

    // Equality operator (==)
    bool operator==(const Flat& other) const {
        return area == other.area;   // Apartments are equal if their areas are equal
    }

    // Greater-than operator (>)
    bool operator>(const Flat& other) const {
        return price > other.price;  // Compare by price
    }

    // Less-than operator (<)
    bool operator<(const Flat& other) const {
        return price < other.price;  // Compare by price
    }

    // Print info about the flat
    void print() {
        cout << "Area: " << area << " m^2, Price: " << price << " USD" << endl;
    }
};

// Testing the Flat class
int main() {
    Flat flat1(60, 75000);
    Flat flat2(60, 82000);
    Flat flat3(45, 50000);

    cout << "flat1 == flat2: " << (flat1 == flat2 ? "Yes" : "No") << endl;
    cout << "flat2 > flat3: " << (flat2 > flat3 ? "Yes" : "No") << endl;
    cout << "flat2 < flat3: " << (flat2 < flat3 ? "Yes" : "No") << endl;

    flat3 = flat1;  // Test assignment
    cout << "\nAfter flat3 = flat1:\n";
    flat3.print();

    return 0;
}
