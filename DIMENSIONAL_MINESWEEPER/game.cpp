#include "common_code.cpp"
#include "game_1d.cpp" // for Game1D function
#include "game_2d.cpp" // for Game2D function
#include "game_3d.cpp" // for Game3D function
#include "game_4d.cpp" // for Game4D function

void Main_Game(int userId) {
    srand(time(NULL));



    char menu[5][50] = {
        "1. 1D Minesweeper",
        "2. 2D Minesweeper",
        "3. 3D Minesweeper",
        "4. 4D Minesweeper",
        "5. Exit"
    };

    bool ExitProgram = false; // Flag to exit the program
    while (!ExitProgram) {
        system("cls");
        cout << "Please choose a game mode:" << endl;

        for (int i = 0; i < 5; i++) {
            cout << menu[i] << endl;
        }

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                Game1D(userId); // Call function for 1D Minesweeper
                system("pause");
                break;
            case 2:
                Game2D(userId); // Call function for 2D Minesweeper
                system("pause");
                break;
            case 3:
                Game3D(userId); // Call function for 3D Minesweeper
                system("pause");
                break;
            case 4:
                Game4D(userId); // Call the Game function for 4D Minesweeper
                system("pause");
                break;
            case 5:
                ExitProgram = true; // Exit the program
                break;
            default:
                cout << "error #6" << endl;
                cout << "Invalid choice. Please try again." << endl;
                system("pause");
        }
    }
}
