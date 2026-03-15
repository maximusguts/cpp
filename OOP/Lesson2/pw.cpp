#include <iostream> // for cout, cin
#include <iomanip>  // for setw
#include <cstdlib>  // for system("cls")
#include <cstring>  // for memset
#include "io.h"     // for _filelength, _fileno
#include <chrono>   // for sleep
#include <thread>   // for sleep too

using namespace std;

class Animal {
    private:
        string species;
        int age;
    public:
        void setSpecies(string newSpecies) {
            species = newSpecies;
        }
        string getSpecies() const { return species; }

        void setAge(int newAge) {
            age = newAge;
        }
        int getAge() const { return age; }

        void walk() const {
            cout << species << " is walking." << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        void jump() const {
            cout << species << " is jumping." << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
};

class Dog : public Animal {
    private:
        string breed;
    public:
        void setBreed(string newBreed) {
            breed = newBreed;
        }
        string getBreed() const { return breed; }

        void bark() const {
            cout << getSpecies() << " the " << breed << " is barking." << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
};

class Cat : public Animal {
    private:
        string color;
    public:
        void setColor(string newColor) {
            color = newColor;
        }
        string getColor() const { return color; }

        void meow() const {
            cout << getSpecies() << " the " << color << " cat is meowing." << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
};

int main()
{
    srand(time(NULL));
    
    Dog myDog = Dog();
    myDog.setSpecies("Dog");
    myDog.setBreed("Labrador");
    myDog.setAge(3);

    cout << "My dog is a " << myDog.getBreed() << " and is " << myDog.getAge() << " years old." << endl;

    for (int i = 0; i < 3; i++) {
        myDog.walk();
        myDog.bark();
        myDog.jump();
    }
    Cat myCat = Cat();
    myCat.setSpecies("Cat");
    myCat.setColor("Black");
    myCat.setAge(2);

    cout << "My cat is a " << myCat.getColor() << " cat and is " << myCat.getAge() << " years old." << endl;

    myCat.walk();
    myCat.meow();

    for (int i = 0; i < 3; i++) {myDog.bark();}
    myDog.walk();
    myDog.jump();

    for (int i = 0; i < 2; i++) {myCat.meow();}
    for (int i = 0; i < 3; i++) {myCat.jump();}
    for (int i = 0; i < 3; i++) {myDog.jump();}

    cout << endl << "End of program." << endl;

    return 0;
}