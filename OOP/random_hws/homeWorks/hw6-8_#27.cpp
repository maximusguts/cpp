#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // For sort, find_if, remove_if
#include <iomanip>   // For nice output formatting (setw)

using namespace std;

// 1. Data Structure
struct Car {
    string name;
    int year;
    double engineVolume;
    double price;

    // Helper to print car info cleanly
    void print() const {
        cout << left << setw(15) << name 
             << " | Year: " << setw(6) << year 
             << " | Engine: " << setw(4) << engineVolume << "L"
             << " | Price: $" << price << endl;
    }
};

// 2. Functors (Required by the task)
// Functor for sorting by Price (Ascending)
struct SortByPrice {
    bool operator()(const Car& a, const Car& b) const {
        return a.price < b.price;
    }
};

// Functor for sorting by Year (Descending - newer first)
struct SortByYear {
    bool operator()(const Car& a, const Car& b) const {
        return a.year > b.year; // Greater year means newer
    }
};

// Functor for Searching (Finding a car by name)
struct FindByName {
    string targetName;
    FindByName(string name) : targetName(name) {}

    bool operator()(const Car& car) const {
        return car.name == targetName;
    }
};

// Main Application Logic
int main() {
    // Container to store cars
    vector<Car> dealership;

    // Pre-populating with some data for testing
    dealership.push_back({"Toyota Camry", 2020, 2.5, 25000});
    dealership.push_back({"BMW X5", 2022, 3.0, 60000});
    dealership.push_back({"Honda Civic", 2018, 1.8, 18000});
    dealership.push_back({"Audi A4", 2021, 2.0, 35000});
    dealership.push_back({"Ford Mustang", 2019, 5.0, 40000});

    int choice;
    do {
        cout << "\n=== CAR DEALERSHIP MENU ===\n";
        cout << "1. Show all cars\n";
        cout << "2. Add a car\n";
        cout << "3. Delete a car (by name)\n";
        cout << "4. Sort by Price (Cheapest first)\n";
        cout << "5. Sort by Year (Newest first)\n";
        cout << "6. Search by Name\n";
        cout << "0. Exit\n";
        cout << "Selection: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\n--- Current Inventory ---\n";
            // Algorithm: for_each (or simply a range-based for loop)
            for (const auto& car : dealership) {
                car.print();
            }
        }
        else if (choice == 2) {
            Car newCar;
            cout << "Enter Name: ";
            cin.ignore(); // Clear buffer
            getline(cin, newCar.name);
            cout << "Enter Year: "; cin >> newCar.year;
            cout << "Enter Engine Volume: "; cin >> newCar.engineVolume;
            cout << "Enter Price: "; cin >> newCar.price;
            dealership.push_back(newCar);
            cout << "Car added!\n";
        }
        else if (choice == 3) {
            string nameToDelete;
            cout << "Enter name to delete: ";
            cin.ignore();
            getline(cin, nameToDelete);

            // Algorithm: remove_if combined with erase (Erase-Remove Idiom)
            auto newEnd = remove_if(dealership.begin(), dealership.end(), FindByName(nameToDelete));

            if (newEnd != dealership.end()) {
                dealership.erase(newEnd, dealership.end());
                cout << "Car deleted.\n";
            } else {
                cout << "Car not found.\n";
            }
        }
        else if (choice == 4) {
            // Algorithm: sort using Functor SortByPrice
            sort(dealership.begin(), dealership.end(), SortByPrice());
            cout << "Sorted by Price!\n";
        }
        else if (choice == 5) {
            // Algorithm: sort using Functor SortByYear
            sort(dealership.begin(), dealership.end(), SortByYear());
            cout << "Sorted by Year!\n";
        }
        else if (choice == 6) {
            string searchName;
            cout << "Enter name to search: ";
            cin.ignore();
            getline(cin, searchName);

            // Algorithm: find_if using Functor FindByName
            auto it = find_if(dealership.begin(), dealership.end(), FindByName(searchName));

            if (it != dealership.end()) {
                cout << "\nFound:\n";
                it->print();
            } else {
                cout << "Not found.\n";
            }
        }

    } while (choice != 0);

    return 0;
}
