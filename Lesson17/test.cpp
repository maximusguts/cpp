#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;



int main()
{
    int a = 123;
    float b = 123.456f;

    char* result = new char[50];
    sprintf(result, "a = %d; b = %f", a, b);

    printf("%s\n", result);
}