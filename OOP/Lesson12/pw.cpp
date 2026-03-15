#include <iostream>
#include <string>
using namespace std;

// Base class
class Animal {
private:
    string* name; // private pointer to data

public:
    Animal(const string& n);
    virtual ~Animal();

    // Virtual function to be overridden
    virtual void Speak();

    string getName() const;
};

// First derived class
class Mammal : public Animal {
private:
    int* age; // private pointer to data

public:
    Mammal(const string& n, int a);
    ~Mammal();

    void Speak() override; // override Speak()
};

// Second derived class (child of Mammal)
class Dog final : public Mammal { // 'final' forbids further inheritance
private:
    string* breed; // private pointer to data

public:
    Dog(const string& n, int a, const string& b);
    ~Dog();

    void Speak() override; // overridden Speak()

    // Friend function to display object state
    friend void ShowDogState(const Dog& d);
};

// Fourth class (direct child of Animal)
class Bird : public Animal {
private:
    string* color; // private pointer to data

public:
    Bird(const string& n, const string& c);
    ~Bird();

    void Speak() override final; // final overridding Speak()
};

// ───────────────────────────────
// Implementation section
// ───────────────────────────────

Animal::Animal(const string& n) {
    name = new string(n);
}

Animal::~Animal() {
    delete name;
}

void Animal::Speak() {
    cout << *name << " makes a sound." << endl;
}

string Animal::getName() const {
    return *name;
}

// ───────────────────────────────

Mammal::Mammal(const string& n, int a) : Animal(n) {
    age = new int(a);
}

Mammal::~Mammal() {
    delete age;
}

void Mammal::Speak() {
    cout << getName() << " (Mammal) makes a soft sound." << endl;
}

// ───────────────────────────────

Dog::Dog(const string& n, int a, const string& b) : Mammal(n, a) {
    breed = new string(b);
}

Dog::~Dog() {
    delete breed;
}

void Dog::Speak() {
    cout << getName() << " the " << *breed << " barks: Woof!" << endl;
}

void ShowDogState(const Dog& d) {
    cout << "Dog info -> name: " << d.getName()
         << ", breed: " << *d.breed << endl;
}

// ───────────────────────────────

Bird::Bird(const string& n, const string& c) : Animal(n) {
    color = new string(c);
}

Bird::~Bird() {
    delete color;
}

void Bird::Speak() {
    Animal::Speak();
}

// ───────────────────────────────

int main() {
    // Array of base-class pointers for dynamic polymorphism
    Animal* animals[3];
    animals[0] = new Mammal("Elephant", 10);
    animals[1] = new Dog("Buddy", 3, "Labrador");
    animals[2] = new Bird("Parrot", "green");

    cout << "--- Animal sounds ---" << endl;
    for (int i = 0; i < 3; i++) {
        animals[i]->Speak(); // dynamic polymorphism in action
    }

    cout << "\n--- Dog state ---" << endl;
    Dog d("Rex", 5, "German Shepherd");
    ShowDogState(d); // friend function can access private data

    // Clean up memory
    for (int i = 0; i < 3; i++)
        delete animals[i];

    return 0;
}
