

#include <iostream>
#include <iomanip>
using namespace std;

struct Person
{
	char name [10]; 
	char surname [15]; 
	int age;
	char gender[10]; 
};

 
int main()
{
    Person persons[3] = 
    {"Ivan", "Niconov", 30, "male", "Alex", "Petrov", 25, "male", "Irene", 
    "Simonova", 20, "female"};
    
    cout << endl << setw(10) << "Name" << setw(10) << "Surname" << setw(10) << "Age" << setw(10) << "Gender\n";
	for(int i = 0; i < 3; i++)
	{
		cout << setw(10) << persons[i].name;
		cout << setw(10) << persons[i].surname;
		cout << setw(10) << persons[i].age;
		cout << setw(10) << persons[i].gender << '\n';
	}

    return 0;
}