#include <iostream>
#include <string>
using namespace std;

const int MAX_VIOLATIONS = 10;  // maximum violations per car

struct CarRecord {
    string violations[MAX_VIOLATIONS]; // fixed-size array
    int count = 0;                     // current number of violations
};

class Node {
public:
    string plateNumber;   // key
    CarRecord record;     // value
    Node* left;
    Node* right;

    Node(const string& plate) : plateNumber(plate), left(nullptr), right(nullptr) {
        record.count = 0;
    }

    Node(const string& plate, const string& violation) : Node(plate) {
        record.violations[0] = violation;
        record.count++;
    }

    void addViolation(const string& violation) {
        if (record.count < MAX_VIOLATIONS) {
            record.violations[record.count++] = violation;
        } else {
            cout << "Violation list full for plate " << plateNumber << endl;
        }
    }

    void delViolation(const string& violation) {
        for (int i = 0; i < record.count; i++) {
            if (record.violations[i] == violation) {
                // shift all elements left
                for (int j = i; j < record.count - 1; j++) {
                    record.violations[j] = record.violations[j + 1];
                }
                record.count--;
                cout << "Violation '" << violation << "' deleted.\n";
                return;
            }
        }
        cout << "Violation '" << violation << "' not found.\n";
    }

    void printViolations() {
        if (record.count == 0) {
            cout << "No violations.\n";
            return;
        }
        for (int i = 0; i < record.count; i++) {
            cout << " - " << record.violations[i] << endl;
        }
    }
};

class DAITree {
private:
    Node* root;

    void insertRec(Node*& node, const string& plate, const string& violation) {
        if (!node) {
            node = new Node(plate, violation);
            return;
        }
        if (plate < node->plateNumber)
            insertRec(node->left, plate, violation);
        else if (plate > node->plateNumber)
            insertRec(node->right, plate, violation);
        else
            node->addViolation(violation); // existing plate, add violation
    }

    void printRec(Node* node) {
        if (!node) return;
        printRec(node->left);
        cout << "Plate: " << node->plateNumber << " -> Violations: ";
        node->printViolations();
        printRec(node->right);
    }

    Node* search(Node* node, const string& plate) {
        if (!node) return nullptr;
        if (plate == node->plateNumber) return node;
        if (plate < node->plateNumber) return search(node->left, plate);
        else return search(node->right, plate);
    }

    void printRangeRec(Node* node, const string& low, const string& high) {
        if (!node) return;
        if (low < node->plateNumber) printRangeRec(node->left, low, high);
        if (low <= node->plateNumber && node->plateNumber <= high) {
            cout << "Plate: " << node->plateNumber << " -> Violations: ";
            for (int i = 0; i < node->record.count; i++)
                cout << node->record.violations[i] << "; ";
            cout << endl;
        }
        if (node->plateNumber < high) printRangeRec(node->right, low, high);
    }

    void deleteRec(Node* node) {
        if (!node) return;
        deleteRec(node->left);
        deleteRec(node->right);
        delete node;
    }

public:
    DAITree() : root(nullptr) {}
    ~DAITree() { deleteRec(root); }

    void addTicket(const string& plate, const string& violation) {
        insertRec(root, plate, violation);
    }

    void printAll() { printRec(root); }

    void printByPlate(const string& plate) {
        Node* node = search(root, plate);
        if (node) {
            cout << "Plate: " << node->plateNumber << " -> Violations: ";
            for (int i = 0; i < node->record.count; i++)
                cout << node->record.violations[i] << "; ";
            cout << endl;
        } else {
            cout << "No record found for plate " << plate << endl;
        }
    }

    void printRange(const string& low, const string& high) {
        printRangeRec(root, low, high);
    }
};

int main() {
    DAITree db;

    db.addTicket("AA1234BB", "Speeding");
    db.addTicket("AA1234BB", "Illegal parking");
    db.addTicket("CC5678DD", "Red light");
    db.addTicket("BB4321CC", "No seatbelt");

    cout << "--- Full Database ---" << endl;
    db.printAll();

    cout << "\n--- Search by Plate 'AA1234BB' ---" << endl;
    db.printByPlate("AA1234BB");

    cout << "\n--- Search by Range 'AA0000AA' - 'BB9999ZZ' ---" << endl;
    db.printRange("AA0000AA", "BB9999ZZ");

    Node car("AH9945BG");
    car.addViolation("Speeding");
    car.addViolation("No seatbelt");
    car.addViolation("Running red light");

    cout << "Before delete:\n";
    car.printViolations();

    car.delViolation("No seatbelt");

    cout << "\nAfter delete:\n";
    car.printViolations();

    return 0;
}
