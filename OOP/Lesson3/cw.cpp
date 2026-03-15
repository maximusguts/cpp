#include<iostream>

class Component {
    private:
        std::string type;

    public:
        Component(const std::string& type) : type(type) {
            std::cout << "  Component: " << type << std::endl;
        }

        ~Component() {
            std::cout << "  ~Component: " << type << std::endl;
        }
};

class Parent {
    protected:
        std::string parentName;
        Component parentComponent;

    public:
        Parent(const std::string& name)
            : parentName(name), parentComponent("Parent-comp") {
            std::cout << "Parent constr: " << parentName << std::endl;
        }

        ~Parent() {
            std::cout << "~Parent: " << parentName << std::endl;
        }
};

class Child : public Parent {
    private:
        std::string childName;
        Component childComponent;

    public:
        Child(const std::string& parentName, const std::string& childName)
            : Parent(parentName),    
            childComponent("Child-comp"), 
            childName(childName) {       
            std::cout << "Child constr: " << childName << std::endl;
        }

        ~Child() {
            std::cout << "~Child: " << childName << std::endl;
        }
};

int main() {
    std::cout << "=== Init demo ===" << std::endl;
    {
        Child child("Papa", "Son");
    }
    std::cout << "=== object destroyed ===\n" << std::endl;
}
