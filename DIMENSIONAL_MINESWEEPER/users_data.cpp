#pragma once

#include "common_code.cpp"

bool Is_Unique_Name(const ArrayUsers au, const char* username) {
    for (int i = 0; i < au.CountUs; i++) {
        if (strcmp(au.ptrUs[i]->username, username) == 0) {
            return false; // Username already exists
        }
    }
    return true; // Username is unique
}

void Search(User** list, int n) {
    system("cls");
    char input_str[50];
    cout << "Enter user name to search: ";
    cin.ignore();
    cin.getline(input_str, 50);

    ToLower(input_str); // convert input to lowercase

    if (n == 0) {
        cout << "No data to search." << endl;
        system("pause");
        return;
    }

    bool found = false;
    for (int i = 0; i < n; i++)
    {
        char* lower_username = new char[strlen(list[i]->username) + 1];
        Strcpy(lower_username, list[i]->username);
        ToLower(lower_username); // convert each title to lowercase

        int match_index = Strstr_index(lower_username, input_str);
        if (match_index >= 0) {
            char template_output[200] = "";
            Strncat(template_output, list[i]->username, match_index);
            Strcat(template_output, "\"");
            Strncat(template_output, list[i]->username + match_index, strlen(input_str));
            Strcat(template_output, "\"");
            Strcat(template_output, list[i]->username + match_index + strlen(input_str));
            cout << "Found: " << template_output << endl << "    With ID: " << list[i]->id << endl << endl;
            found = true;
        }
        delete[] lower_username; // free the temporary string
    }
    
    if (!found) {
        cout << "No matching users found." << endl;
    } else {
        cout << endl << "You can remember user ID or Name to make sure, you are sending message to right User." << endl;
    }
    system("pause");
    return;
}

void Print_Users_Data(const ArrayUsers& au) {
    if (au.CountUs == 0) {
        cout << "No users found." << endl;
        system("pause");
        return;
    }

    cout << "Users List:" << endl << endl;
    cout << setw(5) << "ID" << setw(22) << "Username" << setw(15) << "Minecoins" 
         << setw(10) << "Games" << setw(15) << "Experience" << setw(17) << "Experience (T)" 
         << setw(10) << "Level" << setw(15) << "Win Strike" << setw(15) << "High Score" << setw(15) 
         << "State" << setw(20) << "Password" << setw(16) << "Cur. Messages" << endl << endl;

    char password_template[50];
    char username_template[50];
    for (int i = 0; i < au.CountUs; i++) {
        if (strlen(au.ptrUs[i]->username) >= 18) {
            strncat(username_template, au.ptrUs[i]->username, 15);
            username_template[15] = '\0';
            strcat(username_template, "...");
        } else {
            strcpy(username_template, au.ptrUs[i]->username);
        }
        // strcpy(username_template, au.ptrUs[i]->username);

        if (strlen(au.ptrUs[i]->password) >= 18) {
            strncat(password_template, au.ptrUs[i]->password, 15);
            password_template[15] = '\0';
            strcat(password_template, "...");
        } else {
            strcpy(password_template, au.ptrUs[i]->password);
        }

        int games_played = au.ptrUs[i]->games_played_1D + au.ptrUs[i]->games_played_2D 
                         + au.ptrUs[i]->games_played_3D + au.ptrUs[i]->games_played_4D;

        cout << setw(5) << au.ptrUs[i]->id << setw(2) << "" 
             << setw(20) << username_template 
             << setw(15) << au.ptrUs[i]->minecoins 
             << setw(10) << games_played 
             << setw(15) << au.ptrUs[i]->experience 
             << setw(17) << au.ptrUs[i]->total_experience 
             << setw(10) << au.ptrUs[i]->level 
             << setw(15) << au.ptrUs[i]->win_strike 
             << setw(15) << au.ptrUs[i]->higher_score 
             << setw(15) << (au.ptrUs[i]->state == USER ? "USER" : (au.ptrUs[i]->state == ADMIN ? "ADMIN" : "CREATOR")) << setw(2) << "" 
             << setw(18) << (au.ptrUs[i]->state == CREATOR ? "***" : (au.ptrUs[i]->state == ADMIN ? "***" : password_template)) 
             << setw(16) << au.ptrUs[i]->Count_of_ptrMs 
             << endl << endl;

        strcpy(password_template, "");
        strcpy(username_template, "");
    }
    cout << "Total count of users: " << au.CountUs << endl;
}

void Add_User(ArrayUsers& au, User* user) {
    FILE* f = nullptr;
    fopen_s(&f, "users.txt", "ab");  // open the file for appending

    if (au.ptrUs == nullptr) { // check if the array is not initialized
        au.SizeUs = au.Block; // set initial size
        au.ptrUs = new User*[au.SizeUs]; // allocate memory for the array
    }

    if (au.CountUs >= au.SizeUs) { // Check if the user array is full
        au.SizeUs += au.Block; // Increase the size of the user array
        User** temp = new User*[au.SizeUs]; // Allocate new memory for the user array
        for (int i = 0; i < au.CountUs; i++) {
            temp[i] = au.ptrUs[i]; // Copy existing users to the new array
        }
        delete[] au.ptrUs; // Free old memory
        au.ptrUs = temp; // Point to new memory
    }

    au.ptrUs[au.CountUs] = user; // add new user
    au.CountUs++; // increment user count

    User_for_safe ufs = Convert_User_to_UserForSafe(*user);

    fwrite(&ufs, sizeof(User_for_safe), 1, f); // write user data to the file
    fclose(f); // close the file
}

void Delete_Users_Data(ArrayUsers& au) {
    Clear_File(); // clear the file to delete all users data
    if (au.ptrUs != nullptr) {
        for (int i = 0; i < au.CountUs; i++) {
            delete au.ptrUs[i]; // free each user
        }
        delete[] au.ptrUs; // free the array of pointers
        au.ptrUs = nullptr; // reset pointer to null
    }
    au.CountUs = 0; // reset user count
    au.SizeUs = 0; // reset size
}

void Delete_User(ArrayUsers& au, char id_r_name[]) {
    system("cls");

    for (int i = 0; i < au.CountUs; i++) {
        if (strcmp(Int_to_str(au.ptrUs[i]->id), id_r_name) == 0) {
            if (au.ptrUs[i]->state == ADMIN || au.ptrUs[i]->state == CREATOR) {
                system("cls");
                cout << "error #3" << endl;
                system("pause");
                return;
            }
            for (int j = 0; j < au.ptrUs[i]->Count_of_ptrMs; j++) delete au.ptrUs[i]->ptrMs[j];
            delete[] au.ptrUs[i]->ptrMs;
            delete au.ptrUs[i]; // free the user
            for (int j = i; j < au.CountUs - 1; j++) {
                au.ptrUs[j] = au.ptrUs[j + 1]; // shift remaining users
            }
            au.CountUs--; // decrement user count
            cout << "User with data \"" << id_r_name << "\" has been deleted." << endl;
            system("pause");
            Fill_File_With_Users_Data(au); // update the file after deletion
            return;
        }
    }
    system("cls");
    cout << "error #4" << endl;
    cout << "User with data \"" << id_r_name << "\" not found." << endl;
    system("pause");
}

void Delete_Users_Data_only_users(ArrayUsers& au) {
    int new_count = 0;
    if (au.ptrUs != nullptr) {
        for (int i = 0; i < au.CountUs; i++) {
            if (au.ptrUs[i]->state == USER) {
                delete au.ptrUs[i];
                au.ptrUs[i] = nullptr;
            } else {
                au.ptrUs[new_count++] = au.ptrUs[i];
            }
        }
        au.CountUs = new_count;
        Fill_File_With_Users_Data(au);
    }
}

void Delete_Manage_Function(ArrayUsers& au) {
    if (au.CountUs == 0) {
        system("cls");
        cout << "error #5" << endl;
        cout << "No users to delete." << endl;
        system("pause");
        return;
    }

    int choice;
    cout << "Delete Users Data Menu:" << endl;
    cout << "Choose an option:" << endl;
    cout << "1. Delete all users data" << endl;
    cout << "2. Delete a specific user by ID or Name" << endl;
    cout << "3. Back to Main Menu" << endl;
    cin >> choice;

    switch (choice) {
        case 1:
            Delete_Users_Data_only_users(au); // delete all users data
            cout << "All users data was deleted (except admins and creators)" << endl;
            system("pause");
            return;
        case 2: {
            if (au.CountUs == 0) {
                cout << "No users to delete." << endl;
                system("pause");
                break;
            }
            char id_or_name[50] = "";
            cout << "Enter user ID or Name to delete: ";
            cin.ignore();
            cin.getline(id_or_name, 50);
            Delete_User(au, id_or_name); // delete the user with the specified ID
            system("pause");
            return;
        }
        case 3:
            return; // back to main menu
        default:
        system("cls");
        cout << "error #6" << endl;
        cout << "Invalid choice. Please try again." << endl;
        system("pause");
        return;
    }
}

void InitUserData(User& user) {
    user.minecoins = 0; // Initialize minecoins
    user.games_played_1D = 0; // Initialize games played (1D)
    user.games_played_2D = 0; // Initialize games played (2D)
    user.games_played_3D = 0; // Initialize games played (3D)
    user.games_played_4D = 0; // Initialize games played (4D)
    user.experience = 0; // Initialize experience
    user.total_experience = 0; // Initialize total experience
    user.level = 1; // Initialize level
    user.win_strike = 0; // Initialize win strike
    user.id = -1; // Initialize ID to -1 until assigned
    user.higher_score = 0; // Initialize score
    user.state = USER; // Set user state to USER
    user.ptrMs = nullptr; // Initialize ptrMs to nullptr
    user.Size_of_ptrMs = 0;
    user.Count_of_ptrMs = 0;
    user.Block_of_ptrMs = 10;
    memset(user.username, 0, sizeof(user.username)); // Initialize username to empty
    memset(user.password, 0, sizeof(user.password)); // Initialize password to empty
}

void Edit_user(ArrayUsers& au) {
    bool end = false;
    char find_name[50];
    memset(find_name, 0, 50);
    int pos = 0;

    cin.get(); // to prevent an empty name entering

    char menu_to_edit[4][50] = {
        "1. Username",
        "2. Password",
        "3. Cancel editing",
        "4. Done editing"
    };

    while (!end) {
        system("cls");

        bool end3 = false;
        while (!end3) {
            cout << "choose:" << endl << endl << "1. Continue editing" << endl << "2. Come back" << endl;
            int choice2;
            cin >> choice2;

            switch (choice2) {
                case 1:
                    end3 = true;
                    break;
                case 2:
                    return;
                default:
                    system("cls");
                    cout << "error #6" << endl;
                    cout << "Invalid choice." << endl;
                    system("pause");
                    break;
            }
        }

        cin.ignore(); // to prevent an empty name entering

        system("cls");
        cout << "Enter user name to edit profile: ";
        cin.getline(find_name, 50);

        bool name_exist = !Is_Unique_Name(au, find_name);

        system("cls");
        if (!name_exist) {
            cout << "error #7" << endl;
            cout << "There is no one matching names in list to edit." << endl;
            system("pause");
            continue;
        } else {
            cout << "error #8" << endl;
            pos = Get_position_of_user(au, find_name);
            cout << "There is one matching name on position " << pos << "." << endl;
            system("pause");
        }

        if (au.ptrUs[pos]->state == ADMIN || au.ptrUs[pos]->state == CREATOR) {
            system("cls");
            cout << "error #9" << endl;
            cout << "Unable to edit this user." << endl;
            system("pause");
            continue;
        }

        cout << setw(5) << "ID" << setw(2) << "" << setw(20) << "Username" << setw(15) << "Minecoins" 
             << setw(10) << "Games" << setw(15) << "Experience" << setw(15) << "Experience (T)" << setw(10) << "Level" 
             << setw(15) << "Win Strike" << setw(15) << "High Score" << setw(15) 
             << "State" << setw(2) << "" << setw(18) << "Password" << endl << endl;

        char username_template[50] = "";
        char password_template[50] = "";

        if (strlen(au.ptrUs[pos]->username) >= 18) {
            strncat(username_template, au.ptrUs[pos]->username, 15);
            username_template[15] = '\0';
            strcat(username_template, "...");
        } else {
            strcpy(username_template, au.ptrUs[pos]->username);
        }
        // strcpy(username_template, au.ptrUs[i]->username);

        if (strlen(au.ptrUs[pos]->password) >= 18) {
            strncat(password_template, au.ptrUs[pos]->password, 15);
            password_template[15] = '\0';
            strcat(password_template, "...");
        } else {
            strcpy(password_template, au.ptrUs[pos]->password);
        }

        int games_played = au.ptrUs[pos]->games_played_1D + au.ptrUs[pos]->games_played_2D 
                         + au.ptrUs[pos]->games_played_3D + au.ptrUs[pos]->games_played_4D;

        cout << setw(5) << au.ptrUs[pos]->id << setw(2) << "" 
             << setw(20) << username_template 
             << setw(15) << au.ptrUs[pos]->minecoins 
             << setw(10) << games_played 
             << setw(15) << au.ptrUs[pos]->experience 
             << setw(15) << au.ptrUs[pos]->total_experience 
             << setw(10) << au.ptrUs[pos]->level 
             << setw(15) << au.ptrUs[pos]->win_strike 
             << setw(15) << au.ptrUs[pos]->higher_score 
             << setw(15) << (au.ptrUs[pos]->state == USER ? "USER" : (au.ptrUs[pos]->state == ADMIN ? "ADMIN" : "CREATOR")) << setw(2) << "" 
             << setw(18) << (au.ptrUs[pos]->state == CREATOR ? "***" : (au.ptrUs[pos]->state == ADMIN ? "***" : password_template)) 
             << endl << endl;

        // strcpy(password_template, "");
        // strcpy(username_template, "");
        system("pause");

        char password_change[50];
        strcpy(password_change, au.ptrUs[pos]->password);
        char username_change[50];
        strcpy(username_change, au.ptrUs[pos]->username);

        bool end2 = false;
        while (!end2) {
            system("cls");
            cout << "Choose an operation:" << endl << endl;
            Menu(menu_to_edit, 4);

            int choice;
            cin >> choice;

            bool username_exist = false; // Flag to check if username exists
            char ans[2] = { 0, '\0' };

            switch (choice) {
                case 1:
                    cin.ignore();
                    cout << "Username: ";
                    cin.getline(username_change, 50);
                    if (strlen(username_change) < 3) {
                        cout << "error #10" << endl;
                        cout << "Username must be longer than 2 characters. Please try again." << endl;
                        system("pause");
                        continue; // Exit the function if username is too short
                    }

                    // Check if username already exists
                    // but this is not realy matter because user have unique ID
                    username_exist = !Is_Unique_Name(au, username_change); // Flag to check if username exists

                    if (username_exist) {
                        cout << "error #11" << endl;
                        cout << "Username already exists. Please choose a different username." << endl;
                        system("pause");
                        break; // Exit the function if username already exists
                    }
                    system("cls");
                    cout << "Changes was safed." << endl;
                    system("pause");
                    break;
                case 2:
                cin.ignore();
                    cout << "Password: ";
                    cin.getline(password_change, 50);
                    if (strlen(password_change) <= 3) {
                        cout << "error #12" << endl;
                        cout << "Password must be longer than 3 characters. Please try again." << endl;
                        system("pause");
                        break; // Exit the function if password is too short
                    }
                    system("cls");
                    cout << "Changes was safed." << endl;
                    system("pause");
                    break;
                case 3:
                    system("cls");
                    cin.ignore();
                    cout << "Are you sure cancel all changes? (Y/n)" << endl;
                    cin.getline(ans, 2);

                    if (strcmp(ans, "n") == 0) {
                        system("cls");
                        cout << "Changes was safed. You can changing more." << endl;
                        system("pause");
                        break;
                    }
                    end2 = true;
                    break;
                case 4:
                    end2 = true;
                    strcpy(au.ptrUs[pos]->username, username_change);
                    strcpy(au.ptrUs[pos]->password, password_change);
                    Fill_File_With_Users_Data(au);
                    system("cls");
                    cout << "Data was safed." << endl;
                    system("pause");
                    break;
                default:
                    system("cls");
                    cout << "error #6" << endl;
                    cout << "Invalid choice." << endl;
                    system("pause");
                    break;
            }
        }
    }
}

bool Creator_exist(const ArrayUsers au) {
    for (int i = 0; i < au.CountUs; i++) {
        if (au.ptrUs[i]->state == CREATOR) {
            return true;
        }
    }
    return false;
}

void Main_Users_Data(ArrayUsers& au) {
    au = {nullptr, 0, 0, 10}; // initialize the user array
    Load_Users_Data(au); // load existing users data
}
