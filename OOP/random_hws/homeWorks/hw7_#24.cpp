#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> // For search logic if needed

using namespace std;

// 1. Data Structure
struct DirectoryEntry {
    string name;
    string owner;
    string phone;
    string address;
    string activity;

    // Helper to print entry nicely
    void print() const {
        cout << "--------------------------------\n";
        cout << "Name:     " << name << endl;
        cout << "Owner:    " << owner << endl;
        cout << "Phone:    " << phone << endl;
        cout << "Address:  " << address << endl;
        cout << "Activity: " << activity << endl;
    }
};

// 2. Class to manage the Directory
class DirectoryManager {
private:
    vector<DirectoryEntry> entries;
    const string filename = "directory_data.txt";

public:
    // Constructor loads data from file automatically
    DirectoryManager() {
        loadFromFile();
    }

    void addEntry() {
        DirectoryEntry entry;
        cout << "\n--- Add New Company ---\n";
        
        // Using getline because names/addresses contain spaces
        cin.ignore(); 
        cout << "Enter Firm Name: "; getline(cin, entry.name);
        cout << "Enter Owner: ";     getline(cin, entry.owner);
        cout << "Enter Phone: ";     getline(cin, entry.phone);
        cout << "Enter Address: ";   getline(cin, entry.address);
        cout << "Enter Activity: ";  getline(cin, entry.activity);

        // Add to memory
        entries.push_back(entry);
        
        // Append to file immediately
        saveEntryToFile(entry);
        cout << "Record saved successfully!\n";
    }

    void showAll() const {
        if (entries.empty()) {
            cout << "\nDirectory is empty.\n";
            return;
        }
        cout << "\n=== ALL RECORDS ===\n";
        for (const DirectoryEntry& entry : entries) {
            entry.print();
        }
    }

    // Generic search function to avoid code duplication
    // type: 1=Name, 2=Owner, 3=Phone, 4=Activity
    void search(int type, const string& query) const {
        bool found = false;
        cout << "\n--- Search Results for: '" << query << "' ---\n";

        for (const auto& entry : entries) {
            bool match = false;
            // Simple substring search using string::find()
            // It returns string::npos if not found
            if (type == 1 && entry.name.find(query) != string::npos) match = true;
            else if (type == 2 && entry.owner.find(query) != string::npos) match = true;
            else if (type == 3 && entry.phone.find(query) != string::npos) match = true;
            else if (type == 4 && entry.activity.find(query) != string::npos) match = true;

            if (match) {
                entry.print();
                found = true;
            }
        }

        if (!found) {
            cout << "No records found.\n";
        }
    }

private:
    // --- FILE I/O OPERATIONS ---

    // Appends a single entry to the file
    void saveEntryToFile(const DirectoryEntry& entry) {
        ofstream outFile(filename, ios::app); // ios::app means "append"
        if (!outFile.is_open()) {
            cerr << "Error: Could not open file for writing!\n";
            return;
        }
        // Write each field on a new line for easy reading
        outFile << entry.name << endl;
        outFile << entry.owner << endl;
        outFile << entry.phone << endl;
        outFile << entry.address << endl;
        outFile << entry.activity << endl;
        outFile.close();
    }

    // Loads all entries from file at startup
    void loadFromFile() {
        ifstream inFile(filename);
        if (!inFile.is_open()) {
            // File might not exist yet, which is fine
            return;
        }

        DirectoryEntry temp;
        // We expect 5 lines per record
        while (getline(inFile, temp.name)) {
            getline(inFile, temp.owner);
            getline(inFile, temp.phone);
            getline(inFile, temp.address);
            getline(inFile, temp.activity);
            
            entries.push_back(temp);
        }
        inFile.close();
    }
};

int main() {
    DirectoryManager manager;
    int choice;

    do {
        cout << "\n=== DIRECTORY MENU ===\n";
        cout << "1. Add Entry\n";
        cout << "2. Show All\n";
        cout << "3. Search by Name\n";
        cout << "4. Search by Owner\n";
        cout << "5. Search by Phone\n";
        cout << "6. Search by Activity\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            manager.addEntry();
        } 
        else if (choice == 2) {
            manager.showAll();
        } 
        else if (choice >= 3 && choice <= 6) {
            string term;
            cout << "Enter search term: ";
            cin.ignore();
            getline(cin, term);
            // Pass choice-2 to map inputs 3,4,5,6 to logic types 1,2,3,4
            manager.search(choice - 2, term);
        }

    } while (choice != 0);

    return 0;
}
