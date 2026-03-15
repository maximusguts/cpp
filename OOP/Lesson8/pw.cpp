#include <iostream>
using namespace std;

template<typename T>
class Matrix {
private:
    int rows;
    int cols;
    T** data;
public:
    // Constructor
    Matrix(int r, int c) : rows(r), cols(c) {
        // rows = r;
        // cols = c;
        data = new T*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols];
        }
    }

    // Destructor
    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
    }

    // Access the item (by link)
    // T& at(int r, int c) {
    //     return data[r][c];
    // }

    T* operator[](int r) {
        return data[r];
    }

    // Print matrix
    void print() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    // matrix of integers (3*3)
    Matrix<int> m1(3, 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            m1[i][j] = i * 3 + j + 1; // filling by nums 1..9
        }
    }
    cout << "Matrix<int>:" << endl;
    m1.print();

    // matrix of strings (2*2)
    Matrix<string> m2(2, 2);
    m2[0][0] = "hi";
    m2[0][1] = "there";
    m2[1][0] = "how";
    m2[1][1] = "are you";
    cout << "\nMatrix<string>:" << endl;
    m2.print();

    return 0;
}
