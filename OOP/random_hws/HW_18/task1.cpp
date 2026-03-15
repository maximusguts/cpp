#include <iostream>
#include <string>
using namespace std;

// Base class
class Pet {
protected:
    string name;
    string characteristic;
public:
    Pet(const string& n, const string& c) : name(n), characteristic(c) {}
    virtual void Speak() const {
        cout << name << " makes a sound." << endl;
    }
    virtual void ShowInfo() const {
        cout << "Name: " << name << ", Characteristic: " << characteristic << endl;
    }
    virtual ~Pet() {} // Virtual destructor for safe polymorphism
};

// Derived classes
class Dog : public Pet {
public:
    Dog(const string& n, const string& c) : Pet(n, c) {}
    void Speak() const override {
        cout << name << " says: Woof!" << endl;
    }
};

class Cat : public Pet {
public:
    Cat(const string& n, const string& c) : Pet(n, c) {}
    void Speak() const override {
        cout << name << " says: Meow!" << endl;
    }
};

class Parrot : public Pet {
public:
    Parrot(const string& n, const string& c) : Pet(n, c) {}
    void Speak() const override {
        cout << name << " says: Squawk!" << endl;
    }
};

// --- MAIN ---
int main() {
    Dog d("Buddy", "Loyal and playful");
    Cat c("Mittens", "Likes to nap");
    Parrot p("Polly", "Can mimic speech");

    d.ShowInfo();
    d.Speak();

    c.ShowInfo();
    c.Speak();

    p.ShowInfo();
    p.Speak();

    return 0;
}
