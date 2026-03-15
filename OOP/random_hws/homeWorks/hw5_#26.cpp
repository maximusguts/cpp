#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm> // For transform
#include <cctype>    // For ispunct, tolower

using namespace std;

// Helper function to clean a word:
// 1. Removes punctuation (like commas, dots) from the beginning and end.
// 2. Converts to lowercase so "Word" and "word" are counted as the same.
string cleanWord(const string& rawWord) {
    string cleaned = "";
    
    // Remove punctuation
    for (char c : rawWord) {
        if (!ispunct(c)) {
            cleaned += tolower(c);
        }
    }
    return cleaned;
}

int main() {
    // 1. Create a dummy input file for testing
    const string inputFilename = "input_text.txt";
    const string outputFilename = "frequency_dictionary.txt";

    ofstream tempFile(inputFilename);
    if (tempFile.is_open()) {
        tempFile << "Apple banana apple. Orange, banana! Apple? Grape.";
        tempFile.close();
    } else {
        cout << "[Error] Could not create test file." << endl;
        return 1;
    }

    // 2. Map to store the frequency dictionary
    // Key (string): the word
    // Value (int): the count
    map<string, int> wordFreq;

    // 3. Read from file
    ifstream inputFile(inputFilename);
    if (!inputFile.is_open()) {
        cout << "[Error] Cannot open input file!" << endl;
        return 1;
    }

    string rawWord;
    while (inputFile >> rawWord) {
        string processed = cleanWord(rawWord);
        if (!processed.empty()) {
            // If the word exists, operator[] returns the reference to its value (count)
            // If it doesn't exist, it creates it with value 0, then we increment
            wordFreq[processed]++;
        }
    }
    inputFile.close();

    // 4. Find the most frequent word and prepare output
    ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        cout << "[Error] Cannot open output file!" << endl;
        return 1;
    }

    cout << "--- Word Frequency Dictionary ---\n";
    outputFile << "--- Word Frequency Dictionary ---\n";

    string mostFrequentWord = "";
    int maxCount = 0;

    // Iterator runs through the map. 'it->first' is the key (word), 'it->second' is the value (count)
    for (const auto& pair : wordFreq) {
        // Output to console
        cout << pair.first << ": " << pair.second << endl;
        // Output to file
        outputFile << pair.first << ": " << pair.second << endl;

        // Check for max
        if (pair.second > maxCount) {
            maxCount = pair.second;
            mostFrequentWord = pair.first;
        }
    }

    // 5. Output the most frequent word
    cout << "\n-------------------------------" << endl;
    cout << "Most frequent word: '" << mostFrequentWord << "' (appears " << maxCount << " times)" << endl;

    outputFile << "\n-------------------------------" << endl;
    outputFile << "Most frequent word: '" << mostFrequentWord << "' (appears " << maxCount << " times)" << endl;

    outputFile.close();
    cout << "Results saved to '" << outputFilename << "'." << endl;

    return 0;
}
