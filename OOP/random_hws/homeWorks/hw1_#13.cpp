#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Helper function to check if brackets match
bool isMatchingPair(char open, char close) {
    if (open == '(' && close == ')') return true;
    if (open == '[' && close == ']') return true;
    if (open == '{' && close == '}') return true;
    return false;
}

int main() {
    // Input string example. You can use cin >> or getline(cin, text) for user input.
    // Example 1 (Correct): "({x-y-z} * [x + 2y] - (z + 4x));"
    // Example 2 (Incorrect): "([x-y-z} * [x + 2y) - {z + 4x)];"
    
    string input;
    cout << "Enter the string (ending with ';'): ";
    getline(cin, input);

    stack<char> s;
    string processedString = ""; // To store the string up to the error point
    bool isError = false;

    for (char current : input) {
        // The task states ';' is the end indicator
        if (current == ';') {
            break;
        }

        processedString += current;

        // If it's an opening bracket, push to stack
        if (current == '(' || current == '{' || current == '[') {
            s.push(current);
        }
        // If it's a closing bracket
        else if (current == ')' || current == '}' || current == ']') {
            
            // If stack is empty, it means we have a closing bracket without an opening one
            if (s.empty()) {
                isError = true;
                break;
            }

            // Check if it matches the last opening bracket
            char lastOpen = s.top();
            if (isMatchingPair(lastOpen, current)) {
                s.pop(); // Correct match, remove from stack
            } else {
                // Mismatch found (e.g., '(' with ']')
                isError = true;
                break;
            }
        }
        // Other characters (letters, numbers, operators) are ignored
    }

    // Final check
    if (isError) {
        cout << "\nError found. String up to the error:\n" << processedString << endl;
    } 
    else if (!s.empty()) {
        // If stack is not empty after the loop, some brackets were left open
        cout << "\nError: Some brackets were not closed. Processed string:\n" << processedString << endl;
    } 
    else {
        cout << "\nThe string is correct!" << endl;
    }

    return 0;
}
