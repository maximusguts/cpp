#include "users_data.cpp" // for User, ArrayUsers, Add_User, Main_Users_Data

int SignUp() {
    ArrayUsers au;
    Main_Users_Data(au); // Load user data

    if (au.CountUs >= 900) {
        system("cls");
        cout << "Server is full. Can't add new users.";
        system("pause");
        return -1;
    }

    cout << "Welcome to 4D Minesweeper!" << endl;
    cout << "Please enter your username and password to sign up." << endl;

    int id = -1; // Initial login state
    bool is_logged_in = false; // Initial login state

    cout << "Current number of users: " << au.CountUs << endl;

    User newUser; // Create a new user object
    memset(&newUser, 0, sizeof(User)); // Initialize the user object to zero
    InitUserData(newUser); // Initialize user data

    cin.get();

    for (int j = 0; j < 6; j++)  // Loop until a valid user is created
    {
        cout << "Username: ";
        cin.getline(newUser.username, 50);
        if (strlen(newUser.username) < 3) {
            cout << "Username must be longer than 2 characters. Please try again." << endl;
            system("pause");
            continue; // Exit the function if username is too short
        }

        // Check if username already exists
        // but this is not realy matter because user have unique ID

        bool unique_username = Is_Unique_Name(au, newUser.username); // Flag to check if username exists
        
        if (!unique_username) {
            cout << "Username already exists. Please choose a different username." << endl;
            system("pause");
            continue; // Exit the function if username already exists
        }

        cout << "Password: ";
        cin.getline(newUser.password, 50);
        if (strlen(newUser.password) <= 3) {
            cout << "Password must be longer than 3 characters. Please try again." << endl;
            system("pause");
            continue; // Exit the function if password is too short
        }
        is_logged_in = true; // Set login state to true if username and password are valid
        break; // Exit the loop if username and password are valid
    }

    if (!is_logged_in) {
        cout << "Too many tries. Try sign up later..." << endl;
        system("pause");
        system("cls");
        return -1; // Sign up failed
    }

    // Initialize user ID
    bool id_exists = false; // Flag to check if ID exists
    if (au.CountUs == 0) {
        id = rand() % 1000;
    } else {
        while (true) {
            id = rand() % 1000; // Random ID for demonstration
            for (int i = 0; i < au.CountUs; i++) {
                if (au.ptrUs[i]->id == id) {
                    id_exists = true; // Set flag to true if ID exists
                    break; // Exit the loop if ID exists
                }
            }
            if (!id_exists) {
                break; // Exit the loop if ID does not exist
            }
        }
    }

    newUser.id = id; // Assign the unique ID to the new user

    bool need_set_password = false;
    if (au.CountUs == 0 || !Creator_exist(au)) {
        newUser.state = CREATOR; // Set user state to CREATOR, because this is the first user
        need_set_password = true;
    } else {
        newUser.state = USER;
    }

    system("cls");
    
    User* userPtr = new User; // Create a pointer to the new user
    *userPtr = newUser; // Copy the new user data to the pointer

    if (au.ptrUs == nullptr) { // Check if the user array is not initialized
        au.SizeUs = au.Block; // Set initial size
        au.ptrUs = new User*[au.SizeUs]; // Allocate memory for the user array
    }

    if (id == -1) {
        cout << "Error: Could not assign a unique ID to the user." << endl;
        delete userPtr; // Free allocated memory for user
        return -1; // Sign up failed
    }

    if (!is_logged_in) {
        cout << "Sign up failed. Please try again." << endl;
        return -1; // Sign up failed
    }

    Add_User(au, userPtr); // Add new user
    Main_Users_Data(au);

    cout << "Sign up successful! Welcome, " << newUser.username << "!" << endl;
    // Here you can add code to redirect the user to the main menu or start the game

    FILE* f = nullptr;
    char game_password[50] = {};

    if (fopen_s(&f, "game_password.txt", "rb") == 0 && f != nullptr) {
        fread(game_password, sizeof(game_password), 1, f);
        fclose(f);
        if (!(strcmp(game_password, "GAME_PASSWORD_NOT_INSTALLED") == 0)) {
            need_set_password = false;
        }
    } else {
        strcpy(game_password, "GAME_PASSWORD_NOT_INSTALLED");
    }

    if (need_set_password) {
        cout << "as you are CREATOR (because you are first game user in data\nor account of creator just was deleted),\nyou have to set Game password: ";
        cin.getline(game_password, 50);
        if (strcmp(game_password, "") == 0) {
            system("cls");
            strcpy(game_password, "GAME_PASSWORD_NOT_INSTALLED");
            cout << "Game password not changed." << endl;
            system("pause");
        }
    }

    fopen_s(&f, "game_password.txt", "wb");
    fwrite(game_password, sizeof(char), 50, f); // writing game_password into a file
    fclose(f);

    return newUser.id; // Sign up successful
}
