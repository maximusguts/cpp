#include <iostream>
using namespace std;

template <typename T>
class Node {
private:
    Node<T>* right;
    Node<T>* left;
    T value = 0;
public:
    Node(T v) : value(v), right(nullptr), left(nullptr) {}

    T getValue() { return value; }

    Node<T>*& getRight() { return right; }
    Node<T>*& getLeft() { return left; }

    void setRight(Node<T>*& node) { right = node; }
    void setLeft(Node<T>*& node) { left = node; }
};

template <typename T>
class Tree {
private:
    Node<T>* root;

    void pushRec(Node<T>*& current, T val) {
        if (!current) {
            current = new Node<T>(val);
            return;
        }
        if (val < current->getValue()) {
            pushRec(current->getLeft(), val);
        } else {
            pushRec(current->getRight(), val);
        }
    }

    void printInRightOrderRec(Node<T>* current) {
        if (!current) return;
        printInRightOrderRec(current->getLeft());
        cout << current->getValue() << " ";
        printInRightOrderRec(current->getRight());
    }
public:
    Tree() : root(nullptr) {}

    void push(T val) {
        pushRec(root, val);
    }

    void print() {
        printInRightOrderRec(root);
        cout << endl;
    }
};

int main() {
    Tree<int> tree;
    tree.push(5);
    tree.push(3);
    tree.push(7);
    tree.push(2);
    tree.push(4);
    tree.push(6);
    tree.push(8);

    cout << "Tree in order - ";
    tree.print(); // Output: 2 3 4 5 6 7 8

    return 0;
}
