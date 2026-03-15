#include <iostream>
#include <exception>
using namespace std;

// Exception class for the list
class ListError : public exception {
    string msg;
public:
    ListError(const string& m) : msg(m) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

// Doubly linked list node
struct Node {
    int data;
    Node* prev;
    Node* next;
    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

// Doubly linked list
class DoublyLinkedList {
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_back(int val) {
        try {
            Node* newNode = new Node(val); // may throw bad_alloc
            if (!head) {
                head = tail = newNode;
            } else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        } catch (bad_alloc&) {
            throw ListError("Memory allocation failed for new node!");
        }
    }

    void pop_back() {
        if (!tail) throw ListError("Cannot delete from an empty list!");

        Node* temp = tail;
        if (head == tail) { // only one element
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
    }

    void print() {
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

// Test
int main() {
    DoublyLinkedList list;

    try {
        list.push_back(10);
        list.push_back(20);
        list.push_back(30);
        list.print();

        list.pop_back();
        list.print();

        list.pop_back();
        list.pop_back();
        list.pop_back(); // throws exception!
    } catch (const ListError& e) {
        cout << "List exception: " << e.what() << endl;
    }

    return 0;
}
