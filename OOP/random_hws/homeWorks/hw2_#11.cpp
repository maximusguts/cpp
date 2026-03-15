#include <iostream>

using namespace std;

// 1. Template function to find the Maximum element
template <typename T>
T findMax(T arr[], int size) {
    T maxVal = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

// 2. Template function to find the Minimum element
template <typename T>
T findMin(T arr[], int size) {
    T minVal = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
    }
    return minVal;
}

// 3. Template function to Sort the array (using Bubble Sort)
template <typename T>
void sortArray(T arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements
                T temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// 4. Template function for Binary Search
// Note: Binary search requires the array to be sorted first!
// Returns the index of the element or -1 if not found.
template <typename T>
int binarySearch(T arr[], int size, T key) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key) {
            return mid; // Element found
        }
        if (arr[mid] < key) {
            left = mid + 1; // Look in the right half
        } else {
            right = mid - 1; // Look in the left half
        }
    }
    return -1; // Element not found
}

// 5. Template function to Replace an element at a specific index
template <typename T>
void replaceElement(T arr[], int index, T newValue) {
    // Basic validation implies the user provides a valid index, 
    // but for safety, checking bounds is good practice (omitted for simple HW style)
    arr[index] = newValue;
}

// Helper function to print array
template <typename T>
void printArray(T arr[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    // --- Example with Integers ---
    cout << "=== Integer Array ===" << endl;
    const int iSize = 7;
    int iArr[iSize] = {12, 5, 8, 1, 9, 3, 7};

    cout << "Original: ";
    printArray(iArr, iSize);

    cout << "Max: " << findMax(iArr, iSize) << endl;
    cout << "Min: " << findMin(iArr, iSize) << endl;

    // Replacing element at index 2 with 99
    cout << "Replacing element at index 2 with 99..." << endl;
    replaceElement(iArr, 2, 99);
    printArray(iArr, iSize);

    // Sorting is required for Binary Search
    cout << "Sorting..." << endl;
    sortArray(iArr, iSize);
    printArray(iArr, iSize);

    // Binary Search
    int searchVal = 99;
    int index = binarySearch(iArr, iSize, searchVal);
    if (index != -1) {
        cout << "Binary Search: Value " << searchVal << " found at index " << index << endl;
    } else {
        cout << "Binary Search: Value " << searchVal << " not found." << endl;
    }

    cout << "\n-------------------\n" << endl;

    // --- Example with Doubles (to prove templates work) ---
    cout << "=== Double Array ===" << endl;
    const int dSize = 5;
    double dArr[dSize] = {3.14, 1.1, 9.5, 2.5, 0.5};

    cout << "Original: ";
    printArray(dArr, dSize);

    cout << "Max: " << findMax(dArr, dSize) << endl;
    sortArray(dArr, dSize);
    cout << "Sorted: ";
    printArray(dArr, dSize);

    return 0;
}
