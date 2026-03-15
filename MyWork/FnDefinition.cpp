#include <iostream>
#include <vector>

using namespace std;

class Variable {};

class Equasion {};

class Moudle {};

class Sqrt {};

class Fraction {};

array function_definition_domain() {

}

int main()
{
    srand(time(NULL));
    
    

    return 0;
}

class Variable {
public:
    char look;
    auto tempValue;

    Variable() : look('x'), tempValue(0) {}
    Variable(char l) : look(l), tempValue(0) {}
};

class Equasion {
public:
    string equasion;

    bool isValueInEquasion() {

    }

    template <typename T>
    T solveEquasion() {

    }
};

class Moudle : Equasion {};

class Sqrt : Equasion {};

class Fraction {
public:
    auto number;
    Equasion numerator;
    Equasion denominator;


};
