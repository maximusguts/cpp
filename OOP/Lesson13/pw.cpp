#include <iostream>
#include <regex>
#include <ctime>     // for time()
using namespace std;

// Custom exception class
class InputError : public exception {
    string msg;
public:
    InputError(const string& m) : msg(m) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

int main()
{
    srand(time(NULL)); // seed for rand()

    while (true)
    {
        int secret = rand() % 101; // random number between 0 and 100
        int tries = 7;

        cout << "\n=== Guess the number between 0 and 100 ===" << endl;

        while (tries > 0)
        {
            try {
                string value;
                cout << "Attempt #" << (8 - tries) << ": ";
                cin >> value;

                const regex base_regex("^[0-9]+$");
                if (!regex_match(value, base_regex))
                    throw InputError("This is not a number!");

                int guess = stoi(value);
                if (guess < 0 || guess > 100)
                    throw out_of_range("Enter a number between 0 and 100!");

                if (guess == secret) {
                    cout << "You guessed it!" << endl;
                    break;
                }
                else if (guess < secret)
                    cout << "The secret number is higher." << endl;
                else
                    cout << "The secret number is lower." << endl;

                tries--;
                if (tries == 0)
                    cout << "You lost! The number was: " << secret << endl;
            }
            catch (const InputError& e) {
                cout << e.what() << endl; // doesn't reduce tries
            }
            catch (const out_of_range& e) {
                cout << e.what() << endl; // doesn't reduce tries
            }
            catch (...) {
                cout << "Unknown input error." << endl;
            }
        }

        cout << "\nDo you want to play again? (y/n): ";
        string again;
        cin >> again;
        if (again != "y" && again != "Y")
            break;
    }

    cout << "Thanks for playing!" << endl;
    return 0;
}
