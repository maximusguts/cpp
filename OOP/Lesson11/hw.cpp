#include <iostream>
#include <cmath>
using namespace std;

class Equation {
public:
    virtual void findRoots() = 0; // pure virtual → abstract
    virtual ~Equation() {}        // virtual destructor
};


class LinearEquation : public Equation {
private:
    double a, b; // ax + b = 0
public:
    LinearEquation(double a, double b) : a(a), b(b) {}
    void findRoots() override;
};

class QuadraticEquation : public Equation {
private:
    double a, b, c; // ax^2 + bx + c = 0
public:
    QuadraticEquation(double a, double b, double c) : a(a), b(b), c(c) {}
    void findRoots() override;
};

void LinearEquation::findRoots() {
    if (a == 0) {
        cout << (b == 0 ? "Infinite solutions" : "No solution") << endl;
    } else {
        cout << "x = " << -b / a << endl;
    }
}

void QuadraticEquation::findRoots() {
    double D = b*b - 4*a*c;
    if (D < 0) cout << "No real roots\n";
    else if (D == 0) cout << "x = " << -b / (2*a) << endl;
    else cout << "x1 = " << (-b + sqrt(D)) / (2*a)
               << ", x2 = " << (-b - sqrt(D)) / (2*a) << endl;
}

int main() {
    Equation* eq1 = new LinearEquation(2, -4);
    Equation* eq2 = new QuadraticEquation(1, -3, 2);

    cout << "Linear: "; eq1->findRoots();
    cout << "Quadratic: "; eq2->findRoots();

    delete eq1;
    delete eq2;
    return 0;
}
