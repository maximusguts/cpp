#include <iostream>
#include <string>
using namespace std;

// Base class
class Animal {
protected:
    string name;
public:
    Animal(string n) : name(n) {}

    // Virtual mothod, redefeniting inherits
    virtual void Speak() {
        cout << name << " Making some sound..." << endl;
    }
};

// Class-inherit Dog
class Dog : public Animal {
public:
    Dog(string n) : Animal(n) {}

    void Speak() override {
        cout << name << " Barking: ow ow!" << endl;
    }
};

// Class-inherit Cat
class Cat : public Animal {
public:
    Cat(string n) : Animal(n) {}

    void Speak() override {
        cout << name << " Meowing: meooooow!" << endl;
    }
};

int main() {
    // Creating objects
    Dog dog("Frank");
    Cat cat("Daisy");

    // Call the Speak() method
    dog.Speak();
    cat.Speak();

    // Polymorphism expl
    Animal* a1 = &dog;
    Animal* a2 = &cat;
    a1->Speak();
    a2->Speak();

    return 0;
}
