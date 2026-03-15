#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>  
#include <stdexcept>
using namespace std;

#pragma region Exception hierarchy
// Base exception class for the whole app
class AppException : public exception {
protected:
    string msg;
public:
    AppException(const string& m) : msg(m) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

// Derived exception types
class MathError : public AppException {
public:
    MathError(const string& m) : AppException("Math error: " + m) {}
};

class MemoryError : public AppException {
public:
    MemoryError(const string& m) : AppException("Memory error: " + m) {}
};

class FileError : public AppException {
public:
    FileError(const string& m) : AppException("File error: " + m) {}
};

class InputError : public AppException {
public:
    InputError(const string& m) : AppException("Input error: " + m) {}
};
#pragma endregion


#pragma region Logger class
class Logger {
    string filename;

public:
    Logger(const string& file) : filename(file) {}

    void logResult(const string& name, int attempts) {
        ofstream fout(filename, ios::app);
        if (!fout)
            throw FileError("Could not open file for writing!");

        auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
        fout << put_time(localtime(&now), "%Y-%m-%d %H:%M:%S")
             << " | " << name << " | " << attempts << " attempts\n";
    }

    vector<string> getLastResults(int n = 5) {
        ifstream fin(filename);
        if (!fin)
            throw FileError("Could not open file for reading!");

        vector<string> lines;
        string line;
        while (getline(fin, line)) {
            if (!line.empty())
                lines.push_back(line);
        }

        if (lines.size() > n)
            lines.erase(lines.begin(), lines.end() - n);

        return lines;
    }

    void showLog() {
        try {
            ifstream fin(filename);
            if (!fin)
                throw FileError("The log file could not be opened!");

            string line;
            cout << "\n===== Log content =====\n";
            while (getline(fin, line)) cout << line << '\n';
            cout << "==========================\n";
        }
        catch (const FileError& e) {
            cout << e.what() << endl;
        }
    }
};
#pragma endregion


#pragma region GuessGame class
class GuessGame {
    string playerName;
    Logger logger;
    vector<int> sessionAttempts;

public:
    GuessGame(const string& name, const string& logFile)
             : playerName(name), logger(logFile) {
        try {
            auto results = logger.getLastResults();
            if (!results.empty()) {
                cout << "\nLast 5 results:\n";
                for (auto& r : results) cout << r << '\n';
            }
            else {
                cout << "\nNo results yet.\n";
            }
        }
        catch (const FileError& e) {
            cout << e.what() << endl;
        }
    }

    void playOnce() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(1, 100);
        int target = dist(gen);
        int attempts = 0;

        cout << "\nComputer remembered the number from 1 to 100.\n";

        while (true) {
            cout << "Your guess: ";
            string input;
            cin >> input;

            try {
                // Validate input
                for (char c : input)
                    if (!isdigit(c))
                        throw InputError("Please enter a valid number!");

                int guess = stoi(input);
                if (guess < 1 || guess > 100)
                    throw MathError("Number must be between 1 and 100!");

                attempts++;

                if (guess > target)
                    cout << "Remembered number is smaller!\n";
                else if (guess < target)
                    cout << "Remembered number is bigger!\n";
                else {
                    cout << "You guessed the number in " << attempts << " attempts!\n";
                    sessionAttempts.push_back(attempts);
                    logger.logResult(playerName, attempts);
                    break;
                }
            }
            catch (const InputError& e) {
                cout << e.what() << endl;
            }
            catch (const MathError& e) {
                cout << e.what() << endl;
            }
            catch (const FileError& e) {
                cout << "Logging failed: " << e.what() << endl;
            }
            catch (const exception& e) {
                cout << "Unexpected error: " << e.what() << endl;
            }
        }
    }

    void showStats() const {
        if (sessionAttempts.empty()) {
            cout << "You haven't played this session yet.\n";
            return;
        }

        cout << "\nSession statistics for " << playerName << ":\n";
        for (size_t i = 0; i < sessionAttempts.size(); ++i)
            cout << "  Game " << i + 1 << ": " << sessionAttempts[i] << " attempts\n";
    }

    void showLog() {
        logger.showLog();
    }
};
#pragma endregion


#pragma region Main
int main() {
    cout << "Enter your name: ";
    string name;
    getline(cin, name);

    GuessGame game(name, "guess_log.txt");

    while (true) {
        cout << "\n1 - Play\n2 - Show session stats\n3 - Show log file\n0 - Exit\n> ";
        int cmd;
        if (!(cin >> cmd)) break;
        cin.ignore();

        switch (cmd) {
        case 1: game.playOnce(); break;
        case 2: game.showStats(); break;
        case 3: game.showLog(); break;
        case 0: cout << "Goodbye!\n"; return 0;
        default: cout << "Unknown command!\n"; break;
        }
    }

    return 0;
}
#pragma endregion
