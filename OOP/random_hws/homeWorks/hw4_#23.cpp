#include <iostream>

using namespace std;

// === Namespace Definition ===

// Main namespace for our library
namespace MathLibrary {

    // Sub-namespace for algebraic structures like Fractions
    namespace Algebra {
        
        class Fraction {
        private:
            int numerator;
            int denominator;
        public:
            Fraction(int num, int denom) : numerator(num), denominator(denom) {
                if (denominator == 0) {
                    cout << "[Error] Denominator cannot be zero!" << endl;
                    denominator = 1; 
                }
            }

            void display() const {
                cout << "Fraction: " << numerator << "/" << denominator << endl;
            }
        };
    }

    // Sub-namespace for geometric structures like Points
    namespace Geometry {

        class Point2D {
        private:
            double x, y;
        public:
            Point2D(double xCoord, double yCoord) : x(xCoord), y(yCoord) {}

            void display() const {
                cout << "Point 2D: (" << x << ", " << y << ")" << endl;
            }
        };

        class Point3D {
        private:
            double x, y, z;
        public:
            Point3D(double xCoord, double yCoord, double zCoord) : x(xCoord), y(yCoord), z(zCoord) {}

            void display() const {
                cout << "Point 3D: (" << x << ", " << y << ", " << z << ")" << endl;
            }
        };
    }
}

// === Testing the Namespaces ===

int main() {
    cout << "=== Namespace Demonstration ===\n" << endl;

    // Method 1: Using the full qualified name (Scope Resolution Operator ::)
    // This is the safest way to avoid conflicts.
    MathLibrary::Algebra::Fraction f1(3, 4);
    f1.display();

    MathLibrary::Geometry::Point2D p2(10.5, 20.1);
    p2.display();

    cout << "\n-----------------------------\n" << endl;

    // Method 2: Using 'using namespace' for a specific scope
    // This allows us to use classes from Geometry without typing the prefix every time.
    {
        using namespace MathLibrary::Geometry;
        
        Point3D p3(1.0, 5.0, 9.0);
        cout << "Accessing Point3D without full prefix:" << endl;
        p3.display();
        
        // Note: Fraction is NOT visible here directly because it is in MathLibrary::Algebra
        // Fraction f2(1, 2); // This would cause a compilation error
    }

    cout << "\n-----------------------------\n" << endl;

    // Method 3: Using a namespace alias
    // Useful if the namespace name is very long.
    namespace Alg = MathLibrary::Algebra;
    
    Alg::Fraction f2(5, 8);
    cout << "Accessing Fraction using alias 'Alg':" << endl;
    f2.display();

    return 0;
}
