#include <iostream> // for cout, cin
#include <iomanip>  // for setw
#include <cstdlib>  // for system("cls")
#include <cstring>  // for memset
#include "io.h"     // for _filelength, _fileno

using namespace std;

class Car {
    private:
        string make;
        string model;
        int year;
    public:
        void setMake(string newMake) {
            make = newMake;
        }
        string getMake() const { return make; }

        void setModel(string newModel) {
            model = newModel;
        }
        string getModel() const { return model; }
        
        void setYear(int newYear) {
            year = newYear;
        }
        int getYear() const { return year; }
};

void Print_Car_Data(const Car &car) {
    cout << "Car Make: " << car.getMake() << endl;
    cout << "Car Model: " << car.getModel() << endl;
    cout << "Car Year: " << car.getYear() << endl;
}

int main()
{
    srand(time(NULL));
    
    Car myCar = Car();
    myCar.setMake("Toyota");
    myCar.setModel("Corolla");
    myCar.setYear(2020);

    Print_Car_Data(myCar);

    return 0;
}