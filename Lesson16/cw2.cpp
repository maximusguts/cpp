#include <iostream>
#include <iomanip>
using namespace std;

struct Person
{
	int age;
	char name [10]; 
	char surname [15]; 
	char gender[10]; 
};

 
int main()
{

    Person *p = new Person[2];
    
    for(int i = 0; i < 2; i++)
    {
        cout << "name: ";
        cin >> p[i].name;
        cout << "surname: ";
        cin >> p[i].surname;
        cout << "age: ";
        cin >> p[i].age;
        cout << "gender: ";
        cin >> p[i].gender;
        
    }
    
    Person *p_new = p;
    
    for(int i = 0; i < 2; i++)
    {
        cout << p_new ->  name << "\t" << p_new ->  surname << "\t" <<
        p_new ->  gender << "\t" << p_new ->  age << "\t" << "\n";
        
        p_new++;
    }
    
    delete[] p;

    return 0;
}