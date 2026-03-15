#include <iostream>
using namespace std;

// ---------------- NODE ----------------
template <typename T>
class Node {
private:
    T value;          // value of element
    Node<T>* next;    // pointer to next element
public:
    Node(T val) : value(val), next(nullptr) {}

    T getValue() { return value; }
    Node<T>* getNext() { return next; }

    void setNext(Node<T>* node) { next = node; }
};

// ---------------- STACK ----------------
template <typename T>
class Stack {
private:
    Node<T>* topNode;
public:
    Stack() : topNode(nullptr) {}

    void push(T val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->setNext(topNode);
        topNode = newNode;
    }

    T pop() {
        if (!topNode) {
            throw runtime_error("Stack is empty!");
        }
        Node<T>* temp = topNode;
        topNode = topNode->getNext();
        T val = temp->getValue();
        delete temp;
        return val;
    }

    void print() {
        Node<T>* temp = topNode;
        cout << "[ ";
        while (temp) {
            cout << temp->getValue();
            temp = temp->getNext();
            if (temp) cout << " -> ";
        }
        cout << " ]" << endl;
    }

    ~Stack() {
        while (topNode) {
            Node<T>* temp = topNode;
            topNode = topNode->getNext();
            delete temp;
        }
    }
};

// ---------------- QUEUE ----------------
template <typename T>
class Queue {
private:
    Node<T>* head;
    Node<T>* tail;
public:
    Queue() : head(nullptr), tail(nullptr) {}

    void push(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->setNext(newNode);
            tail = newNode;
        }
    }

    T pop() {
        if (!head) {
            throw runtime_error("Queue is empty!");
        }
        Node<T>* temp = head;
        head = head->getNext();
        if (!head) tail = nullptr;
        T val = temp->getValue();
        delete temp;
        return val;
    }

    void print() {
        Node<T>* temp = head;
        cout << "[ ";
        while (temp) {
            cout << temp->getValue();
            temp = temp->getNext();
            if (temp) cout << " -> ";
        }
        cout << " ]" << endl;
    }

    ~Queue() {
        while (head) {
            Node<T>* temp = head;
            head = head->getNext();
            delete temp;
        }
    }
};

// ---------------- LIST ----------------
template <typename T>
class List {
private:
    Node<T>* head;    // pointer to first element
public:
    List() : head(nullptr) {}

    Node<T>* getFirst() { return head; }

    void add(T val, int id = -1) {
        Node<T>* newNode = new Node<T>(val);
        if (id == -1) {
            if (!head) {
                head = newNode;
            } else {
                Node<T>* temp = head;
                while (temp->getNext() != nullptr) {
                    temp = temp->getNext();
                }
                temp->setNext(newNode);
            }
        } else if (id > -1) {
            if (id == 0) {
                newNode->setNext(head);
                head = newNode;
            } else {
                Node<T>* temp = head;
                int index = 0;

                while (temp != nullptr && index < id - 1) {
                    temp = temp->getNext();
                    index++;
                }

                if (temp == nullptr) {
                    if (!head) {
                        head = newNode;
                    } else {
                        Node<T>* last = head;
                        while (last->getNext() != nullptr) {
                            last = last->getNext();
                        }
                        last->setNext(newNode);
                    }
                } else {
                    newNode->setNext(temp->getNext());
                    temp->setNext(newNode);
                }
            }
        } else {
            return;
        }
    }

    void del(int id) {
        if (!head) { return; }

        if (id == 0) {
            Node<T>* temp = head;
            head = temp->getNext();
            delete temp;
            return;
        }
        
        Node<T>* prev = head;
        int index = 0;

        while (prev != nullptr && index < id - 1) {
            prev = prev->getNext();
            index++;
        }

        if (prev == nullptr || prev->getNext() == nullptr) {
            return;
        }

        Node<T>* nodeToDelete = prev->getNext();
        prev->setNext(nodeToDelete->getNext());
        delete nodeToDelete;
    }

    void print() {
        Node<T>* temp = head;
        cout << "[ ";
        while (temp != nullptr) {
            cout << temp->getValue();
            temp = temp->getNext();
            if (temp) cout << " -> ";
        }
        cout << " ]" << endl;
    }

    ~List() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* nextNode = current->getNext();
            delete current;
            current = nextNode;
        }
    }
};

// ---------------- MAIN ----------------
int main() {
    List<int> IntList;      // list for int
    List<string> StrList;   // list for str

    IntList.add(7);
    IntList.add(77);

    StrList.add("Hello");
    StrList.add("World");

    cout << "First element of int-list: " 
         << IntList.getFirst()->getValue() << endl;

    cout << "First element of str-list: " 
         << StrList.getFirst()->getValue() << endl;

    cout << "Second element of int-list: " 
         << IntList.getFirst()->getNext()->getValue() << endl;

    cout << "Second element of str-list: " 
         << StrList.getFirst()->getNext()->getValue() << endl;


    List<int> lst;
    lst.add(10);        // [10]
    lst.add(20);        // [10, 20]
    lst.add(30);        // [10, 20, 30]
    lst.add(5, 0);      // [5, 10, 20, 30]  (insert to start)
    lst.add(15, 2);     // [5, 10, 15, 20, 30] (insert to position 2)
    lst.add(99, 100);   // [5, 10, 15, 20, 30, 99] (id is to big -> insert to end)

    lst.print();   // [ 5 -> 10 -> 15 -> 20 -> 30 -> 99 ]

    lst.del(0);    // deleting 5
    lst.print();   // [ 10 -> 15 -> 20 -> 30 -> 99 ]

    lst.del(1);    // deleting 15
    lst.print();   // [ 10 -> 20 -> 30 -> 99 ]

    lst.del(5);    // nothing ll changed (index out of limit)
    lst.print();   // [ 10 -> 20 -> 30 -> 99 ]


    // demonstration of Stack
    Stack<int> st;
    st.push(1);
    st.push(2);
    st.print(); // [ 1 -> 2 ]
    cout << "Stack pop: " << st.pop() << endl; // will output 2
    st.print(); // remain - [ 1 ]

    // demonstration of Queue
    Queue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.print(); // [ 1 -> 2 ]
    cout << "Queue pop: " << queue.pop() << endl; // will output 1
    queue.print(); // remain - [ 2 ]

    return 0;
}
