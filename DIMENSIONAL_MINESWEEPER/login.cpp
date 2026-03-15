#include "users_data.cpp"

int Login() {
    ArrayUsers au;
    Main_Users_Data(au); // Load user data
    if (au.CountUs == 0) {
        cout << "No users found. Please sign up first." << endl;
        return -1; // No users to log in
    }

    cout << "Welcome to 4D Minesweeper!" << endl;
    cout << "Please enter your username and password to log in." << endl;

    char username[50];
    char password[50];

    cin.ignore();
    cout << "Username: ";
    cin.getline(username, 50);
    cout << "Password: ";
    cin >> password;
    
    bool userFound = false;
    int id = -1; // Initialize user ID to -1
    
    for (int i = 0; i < au.CountUs; i++) {
        if (strcmp(au.ptrUs[i]->username, username) == 0 && strcmp(au.ptrUs[i]->password, password) == 0) {
            userFound = true;
            cout << "Login successful! Welcome, " << au.ptrUs[i]->username << "!" << endl;
            // Here you can add code to start the game or show the main menu
            id = au.ptrUs[i]->id; // Get user ID
            return id; // Login successful
        }
    }
    if (!userFound) {
        cout << "error #13" << endl;
        cout << "Invalid username or password. Please try again." << endl;
        return -1; // Login failed
    }
    
    return id; // Login successful
}
