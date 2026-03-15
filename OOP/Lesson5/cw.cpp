#include <iostream> // for cout, cin
#include <iomanip>  // for setw
#include <cstdlib>  // for system("cls")
#include <cstring>  // for memset
#include "io.h"     // for _filelength, _fileno
#include <chrono>   // for sleep
#include <thread>   // for sleep too

using namespace std;

class Fraction {
    public:
        int number;
        int numerator;
        int denominator;

        void print() const {
            if (number == 0) {
                cout << numerator << "/" << denominator;
            } else if (numerator == 0 || numerator == denominator) {
                cout << number;
            } else {
                cout << number << " +" << numerator << "/" << denominator;
            }
        }

        Fraction to_improper() const {
            Fraction result = *this;
            if (denominator == 0) {
                result.numerator = 0;
                result.denominator = 1; // avoid division by zero
                return result;
            }
            result.numerator += number * denominator;
            result.number = 0;
            return result;
        }

        Fraction to_correct() const {
            Fraction result = *this;
            if (denominator == 0) {
                result.numerator = 0;
                result.denominator = 1; // avoid division by zero
                return result;
            }
            result.number += numerator / denominator;
            result.numerator = numerator % denominator;
            return result;
        }

        Fraction simplify() {
            Fraction result = *this;
            if (denominator == 0) {
                result.numerator = 0;
                result.denominator = 1; // avoid division by zero
                return result;
            }
            int gcd = 1;
            // Greatest Common Divisor (GCD) calculation
            for (int i = 1; i <= numerator && i <= denominator; i++) {
                if (numerator % i == 0 && denominator % i == 0)
                    gcd = i;
            }
            result.numerator /= gcd;
            result.denominator /= gcd;
            return result;
        }

        Fraction operator+ (const Fraction& other) const {
            Fraction f1_cor = this->to_improper();
            Fraction f2_cor = other.to_improper();
            Fraction result;
            result.number = 0;
            result.numerator = f1_cor.numerator * f2_cor.denominator + f2_cor.numerator * f1_cor.denominator;
            result.denominator = f1_cor.denominator * f2_cor.denominator;
            return result.simplify();
        }

        Fraction operator- (const Fraction& other) const {
            Fraction f1_cor = this->to_improper();
            Fraction f2_cor = other.to_improper();
            Fraction result;
            result.number = 0;
            result.numerator = f1_cor.numerator * f2_cor.denominator - f2_cor.numerator * f1_cor.denominator;
            result.denominator = f1_cor.denominator * f2_cor.denominator;
            return result.simplify();
        }

        Fraction operator* (const Fraction& other) const {
            Fraction f1_cor = this->to_improper();
            Fraction f2_cor = other.to_improper();
            Fraction result;
            result.number = 0;
            result.numerator = f1_cor.numerator * f2_cor.numerator;
            result.denominator = f1_cor.denominator * f2_cor.denominator;
            return result.simplify();
        }

        Fraction operator/ (const Fraction& other) const {
            if (other.numerator == 0) {
                return {0, 0, 1}; // return 0/1 if division by zero
            }
            Fraction f1_cor = this->to_improper();
            Fraction f2_cor = other.to_improper();
            Fraction result;
            result.number = 0;
            result.numerator = f1_cor.numerator * f2_cor.denominator;
            result.denominator = f1_cor.denominator * f2_cor.numerator;
            return result.simplify();
        }

        Fraction operator^ (int power) const {
            Fraction base = this->to_improper().simplify();
            Fraction result = {0, 1, 1};

            if (power == 0) return result;

            int exp = power > 0 ? power : -power;
            result = base;

            for (int i = 1; i < exp; i++) {
            result = result * base;
            }

            if (power < 0) {
                swap(result.numerator, result.denominator);
            }

            return result.simplify();
        }

        Fraction& operator++() {
            this->number += 1;
            return *this;
        }

        Fraction& operator--() {
            this->number -= 1;
            return *this;
        }

        bool operator!() const {
            return numerator == 0;
        }

        bool operator== (const Fraction& other) const {
            Fraction f1_cor = this->to_improper().simplify();
            Fraction f2_cor = other.to_improper().simplify();
            return (f1_cor.numerator == f2_cor.numerator) && (f1_cor.denominator == f2_cor.denominator);
        }

        bool operator!= (const Fraction& other) const {
            return !(*this == other);
        }

        bool operator> (const Fraction& other) const {
            Fraction f1_cor = this->to_improper().simplify();
            Fraction f2_cor = other.to_improper().simplify();
            return (f1_cor.numerator * f2_cor.denominator) > (f2_cor.numerator * f1_cor.denominator);
        }

        bool operator< (const Fraction& other) const {
            Fraction f1_cor = this->to_improper().simplify();
            Fraction f2_cor = other.to_improper().simplify();
            return (f1_cor.numerator * f2_cor.denominator) < (f2_cor.numerator * f1_cor.denominator);
        }

        bool operator>= (const Fraction& other) const {
            return (*this > other) || (*this == other);
        }

        bool operator<= (const Fraction& other) const {
            return (*this < other) || (*this == other);
        }

        string operator()(int idx) const {
            switch (idx) {
                case 0: return std::to_string(number);
                case 1: return std::to_string(numerator);
                case 2: return std::to_string(denominator);
                default: return "INVALID";
            }
        }

        operator int() const {
            return number;
        }

        operator double() const {
            if (denominator == 0) return 0.0; 
            return number + static_cast<double>(numerator) / denominator;
        }
};

int main()
{
    srand(time(NULL));
    
    Fraction f1 = {0, 5, 3};
    f1 = f1.to_correct();
    f1.print();
    cout << " = ";

    f1 = f1.to_improper();
    f1.print();
    cout << endl;
    cout << endl;

    Fraction f2 = {0, 3, 7};
    f2.print();
    cout << endl;
    cout << endl;

    Fraction f3 = f1 - f2;
    f1.print();
    cout << " - ";
    f2.print();
    cout << " = ";
    f3.print();
    cout << " = ";
    f3.to_correct().print();
    cout << endl << endl;

    Fraction f4 = {2, 1, 1};
    f3.print();
    cout << " + ";
    f4.print();
    cout << " = ";
    Fraction f5 = f3 + f4;
    f5.print();
    cout << " = ";
    f5.to_correct().print();
    cout << endl << endl;

    Fraction f6 = {10, 7, 8};
    Fraction f7 = {7, 11, 13};
    f6.print();
    cout << " * ";
    f7.print();
    cout << " = ";
    Fraction f8 = f6 * f7;
    f8.print();
    cout << " = ";
    f8.to_correct().print();
    cout << endl << endl;

    Fraction f9 = {1, 1, 2};
    Fraction f10 = {0, 3, 4};
    f9.print();
    cout << " / ";
    f10.print();
    cout << " = ";
    Fraction f11 = f9 / f10;
    f11.print();
    cout << " = ";
    f11.to_correct().print();
    cout << endl << endl << endl;

    Fraction f12 = {0, 2, 3};
    f12.print();
    cout << " ^ " << 3 << " = ";
    Fraction f13 = f12 ^ 3;
    f13.print();
    cout << " = ";
    f13.to_correct().print();
    cout << endl << endl;

    f12.print();
    cout << " ^ " << 2 << " = ";
    f13 = f12 ^ 2;
    f13.print();
    cout << " = ";
    f13.to_correct().print();
    cout << endl << endl;

    f12.print();
    cout << " ^ " << 1 << " = ";
    f13 = f12 ^ 1;
    f13.print();
    cout << " = ";
    f13.to_correct().print();
    cout << endl << endl;

    f12.print();
    cout << " ^ " << 0 << " = ";
    f13 = f12 ^ 0;
    f13.print();
    cout << " = ";
    f13.to_correct().print();
    cout << endl << endl;

    f12.print();
    cout << " ^ " << -1 << " = ";
    f13 = f12 ^ -1;
    f13.print();
    cout << " = ";
    f13.to_correct().print();
    cout << endl << endl;

    Fraction f14 = {1, 1, 2};
    f14.print();
    cout << " ^ " << -2 << " = ";
    Fraction f15 = f14 ^ -2;
    f15.print();
    cout << " = ";
    f15.to_correct().print();
    cout << endl << endl;

    Fraction f16 = {2, 3, 4};
    f16.print();
    cout << "++ = ";
    (++f16).print();
    cout << endl;
    f16.print();
    cout << endl << endl;

    Fraction f17 = {5, 1, 4};
    f17.print();
    cout << "-- = ";
    (--f17).print();
    cout << endl;
    f17.print();
    cout << endl << endl;

    Fraction f18 = {0, 0, 5};
    f18.print();
    cout << " is zero? " << (!f18 ? "Yes" : "No") << endl << endl;

    Fraction new_f = {3, 1, 2}; // 3 + 1/2

    cout << "f(0) = " << new_f(0) << endl;
    cout << "f(1) = " << new_f(1) << endl;
    cout << "f(2) = " << new_f(2) << endl;
    cout << "f(5) = " << new_f(5) << endl; // INVALID

    int asInt = (int)new_f;
    double asDouble = (double)new_f;

    cout << "As int: " << asInt << endl;
    cout << "As double: " << asDouble << endl;

    return 0;
}