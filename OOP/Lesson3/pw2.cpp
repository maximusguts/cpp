#include <iostream>
#include <string>
using namespace std;

// Base class
class Transport {
protected:
    string color;
public:
    // Constructor of the base class
    Transport(string c) : color(c) {} // initializing color

    string getColor() {
        return color;
    }
};

// Derived class Motorcycle
class Motorcycle : public Transport {
private:
    string lastTireUpdate;
public:
    // Constructor of the derived class
    Motorcycle(string c, string date) 
        : Transport(c), lastTireUpdate(date) {} // calling base class constructor

    string getLastTireUpdate() {
        return lastTireUpdate;
    }
};

int main() {
    // Creating an object of the derived class
    Motorcycle moto("red", "2025-09-09");

    cout << "Color: " << moto.getColor() << endl;
    cout << "Date of last tire upgrade: " << moto.getLastTireUpdate() << endl;

    return 0;
}
