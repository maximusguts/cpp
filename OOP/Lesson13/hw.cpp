#include <iostream>
#include <regex>
using namespace std;

class ListError : public exception {
    string msg;
public:
    ListError(const string& m) : msg(m) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

struct Node {
    int data;
    Node* prev;
    Node* next;
    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};


