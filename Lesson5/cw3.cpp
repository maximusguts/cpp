#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

int Round(double x) {
    if (x - int(x) >= 0.5) {
        return int(x) + 1;
    }
    else {
        return x;
    }
}

int main()
{
    srand(time(NULL));
    
    const int ROWS = 20;
    const int COLS = 3;

    const int range_avans = 1000;
    const int range_zp = 100;

    int arr[ROWS][COLS] = {};

    // cout << setw(3) << "i" << " " << setw(5) << "avns" << " " << setw(5) << "zp " << " " << setw(5) << "total" << "\n\n";

    for (int i = 0; i < ROWS; i++)
    {
        // cout << setw(3) << i << " ";
        for (int j = 0; j < COLS; j++)
        {
            switch (j)
            {
                case 0:
                    arr[i][j] = rand() % range_avans + 1;
                    break;
                case 1:
                    arr[i][j] = (rand() % range_zp) * 1000;
                    break;
                case 2:
                    arr[i][j] = arr[i][j - 1] + arr[i][j - 2];
                    break;
            }
            // cout << setw(5) << arr[i][j] << " ";
        }
        // cout << "\n\n";
    }

    int choice = 0;
    int index = 0;

    do {
        cout << "Verification: Enter your index: ";
        cin >> index;
        if (index < 0 || index >= ROWS) {
            cout << "Invalid index. Try again.\n";
            continue;
        }
        else {
            cout << "Your index: " << index << "\n";
            cout << "avans: " << arr[index][0] << "\n";
            cout << "salary: " << arr[index][1] << "\n";
            cout << "total: " << arr[index][2] << "\n\n";
            break;
        }
    } while (true);

    int password = -1;

    do {
        int past_total = arr[index][2];
        cout << "Choose: 1 - withdraw cash, 2 - top up balance, 3 - transfer to another card, 4 - change index, 5 - show data, 6 - for developers, 7 - exit\n";
        cin >> choice;
        switch (choice)
        {
            case 1: {
                cout << "Withdraw cash\n\n";
                int withdraw;
                do {
                    cout << "How much do you want to withdraw? - ";
                    
                    cin >> withdraw;
                    if (withdraw > past_total) {
                        cout << "You don't have enough money. Try again.\n";
                        continue;
                    }
                    else {
                        arr[index][2] -= withdraw;
                        cout << "You have withdrawn: " << withdraw << "\n";
                        cout << "Your previous total: " << past_total << "\n";
                        cout << "Your new total: " << arr[index][2] << "\n\n";
                        break;
                    }
                } while (true);
                int past_total = arr[index][2];
                break;
            }
            case 2: {
                cout << "Top up balance\n\n";
                int topup;
                
                do {
                    cout << "How much do you want to top up? - ";
                    cin >> topup;
                    if (topup < 0) {
                        cout << "Invalid amount. Try again.\n";
                        continue;
                    }
                    else {
                        arr[index][2] += topup;
                        cout << "You have topped up: " << topup << "\n";
                        cout << "Your previous total: " << past_total << "\n";
                        cout << "Your new total: " << arr[index][2] << "\n\n";
                        break;
                    }
                } while (true);
                int past_total = arr[index][2];
                break;
            }
            case 3: {
                cout << "Transfer to another card\n\n";
                int transfer;
                int transfer_index;
                do {
                    cout << "How much do you want to transfer? - ";
                    cin >> transfer;
                    if (transfer > past_total) {
                        cout << "You don't have enough money. Try again.\n";
                        continue;
                    }
                    cout << "Enter the index of the card you want to transfer to: ";
                    cin >> transfer_index;
                    if (transfer_index < 0 || transfer_index >= ROWS) {
                        cout << "Invalid index. Try again.\n";
                        continue;
                    }
                    else {
                        arr[index][2] -= transfer;
                        arr[transfer_index][2] += transfer;
                        cout << "You have transferred: " << transfer << "\n";
                        cout << "Your previous total: " << past_total << "\n";
                        cout << "Your new total: " << arr[index][2] << "\n\n";
                        break;
                    }
                } while (true);
                int past_total = arr[index][2];
                break;
            }
            case 4: {
                do {
                    cout << "Verification: Enter your index: ";
                    cin >> index;
                    if (index < 0 || index >= ROWS) {
                        cout << "Invalid index. Try again.\n\n";
                        continue;
                    }
                    else {
                        cout << "Your index: " << index << "\n";
                        cout << "avans: " << arr[index][0] << "\n";
                        cout << "salary: " << arr[index][1] << "\n";
                        cout << "total: " << arr[index][2] << "\n\n";
                        break;
                    }
                } while (true);
                past_total = arr[index][2];
                break;
            }
            case 5: {
                cout << "Show data\n\n";
                cout << "Your index: " << index << "\n";
                cout << "avans: " << arr[index][0] << "\n";
                cout << "salary: " << arr[index][1] << "\n";
                cout << "total: " << arr[index][2] << "\n\n";
                break;
            }
            case 6: {
                cout << "For developers\n\n";
                if (password == -1) {
                    cout << "You haven't own password! Enter new password: ";
                    cin >> password;
                }

                do {
                    cout << "Enter your password: ";
                    int pass;
                    cin >> pass;
                    if (pass == password) {
                        cout << "Your password is correct. You want change it? (0 - no; 1 - yes)\n";
                        int change_pass;
                        cin >> change_pass;
                        if (change_pass == 1) {
                            cout << "Enter new password: ";
                            cin >> password;
                            cout << "Your password has been changed.\n\n";
                        }
                        else {
                            cout << "Your password is not changed.\n\n";
                        }
                        break;
                    }
                    else {
                        cout << "Your password is incorrect. You can try again, or anyway go in? (0 - no, i will try again; 1 - yes, let me through please)\n";
                        int try_again;
                        cin >> try_again;
                        if (try_again == 0) {
                            continue;
                        }
                        else {
                            cout << "You have been let through.\n\n";
                            break;
                        }
                        continue;
                    }
                } while (true);
                
                cout << setw(3) << "id" << " " << setw(5) << "avns" << " " << setw(5) << "slry" << " " << setw(5) << "total" << "\n\n";
                for (int i = 0; i < ROWS; i++)
                {
                    cout << setw(3) << i << " ";
                    for (int j = 0; j < COLS; j++)
                    {
                        cout << setw(5) << arr[i][j] << " ";
                    }
                    cout << "\n\n";
                }
                break;
            }
            case 7: {
                cout << "Exit\n";
                break;
            }
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);
            
    return 0;
}