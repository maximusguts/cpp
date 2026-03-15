#include <iostream>
using namespace std;

// Abstract base class
class Shape {
public:
    virtual void Draw() = 0;  // pure virtual function
    virtual ~Shape() {}       // virtual destructor
};

// Derived class: Circle
class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r = 1.0) : radius(r) {}

    void Draw() override {
        cout << "Drawing a Circle with radius " << radius << endl;
    }
};

// Derived class: Rectangle
class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w = 1.0, double h = 1.0) : width(w), height(h) {}

    void Draw() override {
        cout << "Drawing a Rectangle " << width << " x " << height << endl;
    }
};

int main() {
    const int SIZE = 3;
    Shape* shapes[SIZE]; // raw pointer array

    // Fill the array dynamically
    for (int i = 0; i < SIZE; i++) {
        cout << "Enter type for element " << i << " (1=Circle, 2=Rectangle): ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            double r;
            cout << "Enter radius: ";
            cin >> r;
            shapes[i] = new Circle(r);
        }
        else if (choice == 2) {
            double w, h;
            cout << "Enter width and height: ";
            cin >> w >> h;
            shapes[i] = new Rectangle(w, h);
        }
        else {
            cout << "Invalid type! Defaulting to Circle.\n";
            shapes[i] = new Circle();
        }
    }

    cout << "\n--- Drawing all shapes ---\n";
    for (int i = 0; i < SIZE; i++) {
        shapes[i]->Draw(); // polymorphic call
    }

    // Clean up memory
    for (int i = 0; i < SIZE; i++) {
        delete shapes[i];
    }

    return 0;
}
