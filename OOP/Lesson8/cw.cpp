#include <iostream>
using namespace std;


template<typename T>
class MyContainer {
private:
    T value;
public:
    MyContainer(T value) { 
        this->value = value;
    }
    T getValue() {
        return value;
    }
    void setValue(T newValue) {
        value = newValue;
    }
};

template<typename T>
void NewFunction3(T a)
{
    MyContainer<string>* myContainer2 = new MyContainer<string>("abc");
    cout << myContainer2->getValue() << endl;

    int k = strlen("abbb");

    MyContainer<int>* myContainer = new MyContainer<int>(5);
    cout << myContainer->getValue() << endl;
    myContainer->setValue(10);
    cout << myContainer->getValue() << endl;
    delete myContainer;

    delete myContainer2;
}


int main() {
    NewFunction3(5);
    return 0;
}
 