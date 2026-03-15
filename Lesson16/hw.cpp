#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct fraction
{
    int number;
    int numerator;
    int denominator;
};
                                                          
void print_fraction(const fraction& f)
{
    if (f.number == 0) {
        cout << f.numerator << "/" << f.denominator;
    } else {
        cout << f.number << " +" << f.numerator << "/" << f.denominator;
    }
    
}

fraction correct_to_incorrect(fraction f)
{
    fraction result = f;
    result.numerator += f.number * f.denominator;
    result.number = 0;
    return result;
}

fraction incorrect_to_correct(fraction f)
{
    fraction result = f;
    result.number += f.numerator / f.denominator;
    result.numerator = f.numerator % f.denominator;
    return result;
}

fraction add_fractions(const fraction& f1, const fraction& f2)
{
    fraction result;
    result.number = 0;
    fraction f1_cor = correct_to_incorrect(f1);
    fraction f2_cor = correct_to_incorrect(f2);
    result.numerator = f1_cor.numerator * f2_cor.denominator + f2_cor.numerator * f1_cor.denominator;
    result.denominator = f1_cor.denominator * f2_cor.denominator;
    return result;
}

fraction subtract_fractions(const fraction& f1, const fraction& f2)
{
    fraction result;
    result.number = 0;
    fraction f1_cor = correct_to_incorrect(f1);
    fraction f2_cor = correct_to_incorrect(f2);
    result.numerator = f1_cor.numerator * f2_cor.denominator - f2_cor.numerator * f1_cor.denominator;
    result.denominator = f1_cor.denominator * f2_cor.denominator;
    return result;
}

fraction multiply_fractions(const fraction& f1, const fraction& f2)
{
    fraction result;
    result.number = 0;
    fraction f1_cor = correct_to_incorrect(f1);
    fraction f2_cor = correct_to_incorrect(f2);
    result.numerator = f1_cor.numerator * f2_cor.numerator;
    result.denominator = f1_cor.denominator * f2_cor.denominator;
    return result;
}

fraction divide_fractions(const fraction& f1, const fraction& f2)
{
    if (f2.numerator == 0) {
        return {0, 0, 1}; // return 0/1 if division by zero
    }
    fraction result;
    result.number = 0;
    fraction f1_cor = correct_to_incorrect(f1);
    fraction f2_cor = correct_to_incorrect(f2);
    result.numerator = f1_cor.numerator * f2_cor.denominator;
    result.denominator = f1_cor.denominator * f2_cor.numerator;
    return result;
}

fraction simplify_fraction(const fraction& f)
{
    fraction result = f;
    int gcd = 1;
    // Gratest Common Divisor (GCD) calculation
    for (int i = 1; i <= f.numerator && i <= f.denominator; i++)
    {
        if (f.numerator % i == 0 && f.denominator % i == 0)
            gcd = i;
    }
    result.numerator /= gcd;
    result.denominator /= gcd;
    
    return result;
}



int main()
{
    srand(time(NULL));
    
    fraction myfrac = {0, 5, 3};

    // checking how works remaking incorrect fractions to correct, and the other way around.

    print_fraction(myfrac);
    cout << endl;
    
    myfrac = incorrect_to_correct(myfrac);
    print_fraction(myfrac);
    cout << endl;
    
    myfrac = correct_to_incorrect(myfrac);
    print_fraction(myfrac);
    cout << endl;
    
    cout << endl;
    
    fraction myfrac2 = {0, 3, 7};
    // printing myfrac2 (for easily)
    print_fraction(myfrac2);
    cout << endl;
    
    cout << endl;
    
    // how subtraction works
    
    print_fraction(myfrac);
    cout << " - ";
    print_fraction(myfrac2);
    cout << " = ";
    fraction myfrac_1_2_res = subtract_fractions(myfrac, myfrac2);
    print_fraction(myfrac_1_2_res);
    
    cout << " = ";
    print_fraction(incorrect_to_correct(subtract_fractions(myfrac, myfrac2)));
    cout << endl << endl;
    
    fraction myfrac3 = {2, 1, 1};
    
    // how adding works
    
    print_fraction(myfrac_1_2_res);
    cout << " + ";
    print_fraction(myfrac3);
    cout << " = ";
    print_fraction(add_fractions(myfrac_1_2_res, myfrac3));
    
    cout << " = ";
    print_fraction(incorrect_to_correct(add_fractions(myfrac_1_2_res, myfrac3)));
    cout << endl << endl;
    
    fraction myfrac1_1 = {10, 7, 8};
    fraction myfrac1_2 = {7, 11, 13};
    
    // how multiplying works
    
    print_fraction(myfrac1_1);
    cout << " * ";
    print_fraction(myfrac1_2);
    cout << " = ";
    
    myfrac1_1 = correct_to_incorrect(myfrac1_1);
    myfrac1_2 = correct_to_incorrect(myfrac1_2);
    
    print_fraction(myfrac1_1);
    cout << " * ";
    print_fraction(myfrac1_2);
    cout << " = ";
    
    print_fraction(multiply_fractions(myfrac1_1, myfrac1_2));
    cout << " = ";
    print_fraction(simplify_fraction(multiply_fractions(myfrac1_1, myfrac1_2)));
    cout << endl << endl;
    
    // and finaly, how dividing works
    
    print_fraction(myfrac1_1);
    cout << " / ";
    print_fraction(myfrac1_2);
    cout << " = ";
    
    print_fraction(divide_fractions(myfrac1_1, myfrac1_2));
    
    cout << " = ";
    print_fraction(simplify_fraction(divide_fractions(myfrac1_1, myfrac1_2)));

    return 0;
}