#include "game.cpp"
#include "login.cpp"
#include "sign_up.cpp"
#include "Messanger_host.cpp"

class Hints // Please, don`t pay attention that i used class for this, it just a hints (/\-/\) 
{
private:
    const char hints[7][100] = {
        "Fun fact: Minesweeper was originally developed for Windows 3.1 in 1990.",
        "Tip: Use the arrows* buttons to mark suspected mines. \n   /\\\n < \\/ >",
        "Tip: Use the kayboard* buttons to move throgh dimensions. \n   W\n A S d",
        "Remember: The more you play, the better you get at Minesweeper!",
        "Pro tip: If you find a number, it indicates how many mines are adjacent to that cell.",
        "Did you know? Minesweeper is a great way to improve your logical thinking skills.",
        "Hint: If you are stuck, try to clear the edges of the board first."
    };
public:
    void Print_random_hint() {
        srand(time(NULL)); // Seed the random number generator
        int random_index = rand() % (sizeof(hints) / sizeof(hints[0]));
        cout << hints[random_index] << endl;
        system("pause");
    }

    void Print_all_hints() {
        for (const char* hint : hints) {
            cout << hint << endl << endl;
        }
        system("pause");
    }
};

void Print_welcome_message() {
    cout << "Welcome to the Dimensional Minesweeper!" << endl;
    cout << "This game is a fun and challenging way to test your logic skills." << endl;
    cout << "Remember, the goal is to clear the board without hitting any mines." << endl;
    cout << "Good luck and have fun!" << endl;
}

int Get_Login_Status()
{
    FILE* f = nullptr;
    fopen_s(&f, "user_id.txt", "rb");  // Open the file to check login status
    if (f == nullptr) {
        return -1; // If the file does not exist, user is not logged in
    }
    int id;
    fread(&id, sizeof(int), 1, f); // Read the login status
    fclose(f);
    return id; // Return the login status
}

void Safe_Login_Status(int id) {
    FILE* f = nullptr;
    fopen_s(&f, "user_id.txt", "wb");  // Save login state to a file
    if (f != nullptr) {
        fwrite(&id, sizeof(int), 1, f);
        fclose(f);
    } else {
        cout << "Error saving login state." << endl;
        system("pause");
    }
}

void Del_Login_Status() {
    FILE* f = nullptr;
    fopen_s(&f, "user_id.txt", "wb");  // Reset login status
    if (f != nullptr) {
        bool is_logged_in = false; // Set to false to indicate user is logged out
        fwrite(&is_logged_in, sizeof(bool), 1, f);
    } else {
        cout << "Error resetting login state." << endl;
    }
    fclose(f);
}

char user_menu[5][50] = { "1. Earn minecoins", "2. Level up", "3. Massanger (demo version)", "4. Access special features (not ready yet)", "5. Come back to main menu" };
char admin_menu[7][50] = { "1. Earn minecoins", "2. Level up", "3. Massanger (demo version)", "4. Access special features (not ready yet)", 
                             "5. Manage users (not ready yet)", "6. View system statistics (not ready yet)", "7. Come back to main menu" };
char creator_menu[8][50] = { "1. Earn minecoins", "2. Level up", "3. Massanger (demo version)", "4. Manage users (not ready yet)", 
                             "5. View system statistics (not ready yet)", "6. Create new features (not ready yet)", 
                             "7. Change game password (not ready yet)", "8. Come back to main menu" };


void User_Opportunities(ArrayUsers& au, int id)
{
    for (int i = 0; i < au.CountUs; i++) {
        if (au.ptrUs[i]->id == id) {
            bool end_id_4 = false;
            while (!end_id_4) {
                int choice = 0;
                system("cls");
                if (au.ptrUs[i]->state == USER) Menu(user_menu, 5);
                else if (au.ptrUs[i]->state == ADMIN) Menu(admin_menu, 7);
                else if (au.ptrUs[i]->state == CREATOR) Menu(creator_menu, 8);
                else end_id_4 = true; // Unknown state, exit loop
                
                cin >> choice;
                cin.ignore();
                switch (choice) {
                    case 1:
                        system("cls");
                        cout << "How to earn minecoins?" << endl << endl;
                        cout << "After any win in game (not after 1D), you earning minecoins." << endl;
                        cout << "If you playing harder games, you will may getting more minecoins." << endl;
                        system("pause");
                        break;
                    case 2:
                        system("cls");
                        cout << "How to level up?" << endl << endl;
                        cout << "You need to earn experiense (like minecoins) to level up." << endl;
                        cout << "for any next level, you need earn more experiense." << endl;
                        system("pause");
                        break;
                    case 3:
                        system("cls");
                        Messanger(au, id);
                        break;
                    case 4:
                        if (au.ptrUs[i]->state == USER || au.ptrUs[i]->state == ADMIN) {
                            system("cls");
                            system("pause");
                        } else if (au.ptrUs[i]->state == CREATOR) {
                            system("cls");
                            system("pause");
                        }
                        break;
                    case 5:
                        if (au.ptrUs[i]->state == USER) {
                            system("cls");
                            end_id_4 = true;
                        } else if (au.ptrUs[i]->state == ADMIN) {
                            system("cls");
                            system("pause");
                        } else if (au.ptrUs[i]->state == CREATOR) {
                            system("cls");
                            system("pause");
                        }
                        break;
                    case 6:
                        if (au.ptrUs[i]->state == USER) {
                            cout << "Invalid choice." << endl;
                            system("pause");
                        } else if (au.ptrUs[i]->state == ADMIN) {
                            system("cls");
                            system("pause");
                        } else if (au.ptrUs[i]->state == CREATOR) {
                            system("cls");
                            system("pause");
                        }
                        break;
                    case 7:
                        if (au.ptrUs[i]->state == USER) {
                            cout << "Invalid choice." << endl;
                            system("pause");
                        } else if (au.ptrUs[i]->state == ADMIN) {
                            system("cls");
                            end_id_4 = true;
                        } else if (au.ptrUs[i]->state == CREATOR) {
                            system("cls");
                            char game_password_temp[50];
                            memset(game_password_temp, 0, 50);
                            Get_Game_Password(game_password_temp);
                            cout << "Entter a new password (Enter to cancel): ";
                            cin.getline(game_password_temp, 50);
                            if (strcmp(game_password_temp, "") == 0) {
                                system("cls");
                                cout << "Game password not changed." << endl;
                                system("pause");
                            } else {
                                system("cls");
                                FILE* f;
                                fopen_s(&f, "game_password.txt", "wb");
                                fwrite(game_password_temp, sizeof(char), 50, f); // writing game_password into a file
                                fclose(f);
                                cout << "Game password was changed." << endl;
                                system("pause");
                            }
                        }
                        break;
                    case 8:
                        if (au.ptrUs[i]->state == USER) {
                            cout << "Invalid choice." << endl;
                            system("pause");
                        } else if (au.ptrUs[i]->state == ADMIN) {
                            cout << "Invalid choice." << endl;
                            system("pause");
                        } else if (au.ptrUs[i]->state == CREATOR) {
                            system("cls");
                            end_id_4 = true;
                        }
                        break;
                    default:
                        cout << "Invalid choice." << endl;
                        system("pause");
                        break;
                }
            }
            break;
        }
    }
    return;
}

void Show_Instructions()
{
    cout << "Instructions for Dimensional Minesweeper:" << endl;
    cout << "1. Use the arrow keys to navigate." << endl;
    cout << "2. Press 'Enter' to select a cell." << endl;
    cout << "3. Avoid mines and try to clear the field." << endl;
    cout << "4. Use numbers to determine the number of adjacent mines." << endl;
    cout << "5. Good luck!" << endl;
}

void Show_Profile(ArrayUsers& au, int id)
{
    for (int i = 0; i < au.CountUs; i++) {
        if (au.ptrUs[i]->id == id) {
            bool end = false;
            while (!end) {
                cout << "Profile of " << au.ptrUs[i]->username << endl << endl;

                cout << "1. Show game data" << endl;
                cout << "2. Show local data" << endl;
                cout << "3. Back to main menu" << endl;
                
                int games_played = au.ptrUs[i]->games_played_1D + au.ptrUs[i]->games_played_2D 
                                 + au.ptrUs[i]->games_played_3D + au.ptrUs[i]->games_played_4D;

                char temp[5] = "";
                int choice;
                cin >> choice;

                switch (choice) {
                    case 1:
                        system("cls");
                        cout << "Game Data:" << endl;
                        cout << "Minecoins: " << au.ptrUs[i]->minecoins << endl;
                        cout << "Games Played: " << games_played << endl;
                        cout << "Experience: " << au.ptrUs[i]->experience << endl;
                        cout << "Level: " << au.ptrUs[i]->level << endl;
                        cout << "Win Strike: " << au.ptrUs[i]->win_strike << endl;
                        cout << "High Score: " << au.ptrUs[i]->higher_score << endl << endl;
                        cout << "Type '1' to show more details: ";
                        cin.ignore();
                        cin.getline(temp, 5);

                        if (strcmp(temp, "1") == 0) {
                            system("cls");
                            cout << "Game Data:" << endl;
                            cout << "Minecoins: " << au.ptrUs[i]->minecoins << endl;
                            cout << "Games Played (1D): " << au.ptrUs[i]->games_played_1D << endl;
                            cout << "Games Played (2D): " << au.ptrUs[i]->games_played_2D << endl;
                            cout << "Games Played (3D): " << au.ptrUs[i]->games_played_3D << endl;
                            cout << "Games Played (4D): " << au.ptrUs[i]->games_played_4D << endl;
                            cout << "Experience: " << au.ptrUs[i]->experience << endl;
                            cout << "Level: " << au.ptrUs[i]->level << endl;
                            cout << "Win Strike: " << au.ptrUs[i]->win_strike << endl;
                            cout << "High Score: " << au.ptrUs[i]->higher_score << endl << endl;
                            system("pause");
                        }

                        system("cls");
                        continue;
                    case 2:
                        system("cls");
                        cout << "Local Data:" << endl;
                        cout << "ID: " << au.ptrUs[i]->id << endl;
                        cout << "Username: " << au.ptrUs[i]->username << endl;
                        cout << "Password: " << au.ptrUs[i]->password << endl;
                        cout << "State: " << (au.ptrUs[i]->state == USER ? "USER" : (au.ptrUs[i]->state == ADMIN ? "ADMIN" : "CREATOR")) << endl;
                        system("pause");
                        system("cls");
                        continue;
                    case 3:
                        end = true; // Exit the profile menu
                        system("cls");
                        continue; // Go back to the main menu
                    default:
                        cout << "Invalid choice." << endl;
                        system("pause");
                        continue;
                }
            }
        }
    }
}

int main()
{
    srand(time(NULL));

    FILE* f = nullptr;
    fopen_s(&f, "users.txt", "ab");
    fclose(f);

    fopen_s(&f, "users_messages.txt", "ab");
    fclose(f);

    fopen_s(&f, "posts.txt", "ab");
    fclose(f);

    // Creating files if it doesn't exist.

    char game_password[50];
    memset(game_password, 0, 50);
    Get_Game_Password(game_password);
    
    ArrayUsers au;
    Main_Users_Data(au); // Load user data

    int id = Get_Login_Status(); // Check if the user is logged in
    
    // Game();
    bool ExitProgram = false;

    char menu_before_log_in[4][50] = {
        "1. Log In",
        "2. Sign Up",
        "3. For developers",
        "4. Exit"
    };

    char menu_after_log_in[6][50] = {
        "1. Start Game",
        "2. Show Instructions",
        "3. My Profile",
        "4. My opportunities",
        "5. Log Out",
        "6. Exit"
    };

    char dev_menu[5][50] = {
        "1. Show Developer Info",
        "2. Show users list",
        "3. Delete Users Data",
        "4. Edit Users Data",
        "5. Back to Main Menu"
    };

    Hints hints;
    system("cls");
    cout << "**DIMENSIONAL MINESWEEPER**" << endl << endl;
    Print_welcome_message(); // Print welcome message
    cout << endl;
    hints.Print_random_hint(); // Print a random hint at the start

    while (!ExitProgram) {
        system("cls");
        cout << "**DIMENSIONAL MINESWEEPER**" << endl << endl;
        cout << "Welcome to Game!" << endl;

        if (id != -1) {
            bool log_in_error = false; // Flag to check if login was successful
            for (int i = 0; i < au.CountUs; i++) {
                if (au.ptrUs[i]->id == id) {
                    cout << "Logged in as: " << au.ptrUs[i]->username << endl;
                    log_in_error = true; // Set flag to true if user is found
                    break; // Exit loop after finding the user
                }
            }
            if (!log_in_error) {
                cout << "Error: User not found. Please log in again.\nerror #1" << endl;
                id = -1; // Reset ID if user not found
                Safe_Login_Status(id); // Save login state
                system("pause");
                continue; // Skip to the next iteration of the loop
            }
            // Show menu for logged-in users
            cout << endl << "Please choose an option:" << endl;
            Menu(menu_after_log_in, 6);
            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    Main_Game(id); // Start Game
                    break; // Continue to the next iteration of the loop
                case 2:
                    cout << "Instructions: ..."; // Show Instructions
                    system("pause");
                    break;
                case 3:
                    system("cls");
                    Show_Profile(au, id); // Show Profile
                    break;
                case 4:
                    system("cls");
                    cout << "My Opportunities: " << endl;
                    User_Opportunities(au, id); // Show My Opportunities
                    break;
                case 5:
                    system("cls");
                    id = -1; // Log Out
                    Safe_Login_Status(id); // Save login state
                    // Del_Login_Status(); // Reset login status
                    cout << "You have been logged out." << endl;
                    system("pause");
                    break;
                case 6:
                    ExitProgram = true; // Exit
                    break;
                default:
                    system("cls");
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }
        } else {
            // Show menu for users not logged in
            Menu(menu_before_log_in, 4);

            int choice;
            cin >> choice;
            bool end_id_3 = false;

            switch (choice) {
                case 1: {
                    system("cls");
                    id = Login(); // Log In
                    Safe_Login_Status(id); // Save login state
                    system("pause");
                    break;
                }
                case 2: {
                    system("cls");
                    id = SignUp(); // Sign Up
                    Safe_Login_Status(id); // Save login state
                    if (id == -1) {
                        cout << "You`ve got an error: Sign up fail" << endl;
                    } else {
                        cout << "You are now signed up. Your ID is: " << id << endl;
                    }
                    Main_Users_Data(au); // Reload user data after sign up
                    Get_Game_Password(game_password);
                    system("pause");
                    break;
                }
                case 3: {
                    bool enter_acces = false;
                    cin.ignore();
                    system("cls");
                    Get_Game_Password(game_password);
                    if (strcmp(game_password, "GAME_PASSWORD_NOT_INSTALLED") == 0) {
                        cout << "Game password not set yet. This option is not available now. Try later." << endl;
                        system("pause");
                    } else {
                        char gmpswrd[50] = "";
                        cout << "Enter game password: ";
                        cin.getline(gmpswrd, 50);

                        if (strcmp(gmpswrd, game_password) == 0) {
                            enter_acces = true;
                        }
                    }

                    if (strcmp(game_password, "GAME_PASSWORD_NOT_INSTALLED") == 0) {
                        break;
                    }

                    if (enter_acces) {
                        system("cls");
                        cout << "password correct. you can come in." << endl;
                        system("pause");
                    } else {
                        system("cls");
                        cout << "password incorrect. please, try later." << endl;
                        system("pause");
                        break;
                    }

                    while (!end_id_3) {
                        system("cls");
                        cout << "Developer Menu:" << endl;
                        Menu(dev_menu, 5);
                        int dev_choice;
                        cin >> dev_choice;
                        switch (dev_choice) {
                            case 1: {
                                system("cls");
                                cout << "Developer: Maxim H." << endl;
                                cout << "Email: maximguts@gmail.com" << endl;
                                cout << "GitHub: maximusguts " << endl;
                                cout << "Telegram: @erkkas_193" << endl;
                                cout << "This game is a simple implementation of Minesweeper in 4D." << endl;
                                cout << "It is a work in progress and may contain bugs." << endl;
                                cout << "Thank you for playing!" << endl;
                                system("pause");
                                continue;
                            }
                            case 2: {
                                system("cls");
                                Print_Users_Data(au); // Show users list
                                system("pause");
                                continue;
                            }
                            case 3: {
                                system("cls");
                                Delete_Manage_Function(au);
                                system("cls");
                                continue; // Continue to the next iteration of the loop
                            }
                            case 4: {
                                system("cls");
                                Edit_user(au);
                                continue;
                            }
                            case 5: {
                                // Back to Main Menu
                                end_id_3 = true;
                                continue;
                            }
                            default: {
                                cout << "Invalid choice. Please try again." << endl;
                                continue;
                            }
                            system("pause");
                        }
                        continue;
                    }
                    continue; // Continue to the next iteration of the loop
                }
                case 4: {
                    ExitProgram = true; // Exit
                    break;
                }
                case 193: {
                    remove("game_password.txt");
                    remove("user_id.txt");
                    remove("users_messages.txt");
                    remove("users.txt");
                    ExitProgram = true; // Exit
                    break;
                }
                default: {
                    cout << "Invalid choice. Please try again." << endl;
                    break;
                }
            }
        }
    }
    system("cls");
    return 0;
}
