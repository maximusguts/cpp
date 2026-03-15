#include "common_code.cpp"
#include "game_logic.cpp"

void initField(short *field, short size, short mines) {
    for (short i = 0; i < size; i++) {
        field[i] = 0; // initialize all cells to 0
    }

    // Place mines randomly
    short rest_mines = mines; // Remaining mines to place
    while (rest_mines > 0)
    {
        short pos = rand() % size;

        if (field[pos] == 0) { // Check if the cell is empty
            field[pos] = -1; // -1 indicates a mine
            rest_mines--; // Decrease remaining mines
        } else {
            continue; // If not empty, skip to next iteration
        }
    }

    // Count adjacent mines
    for (short i = 0; i < size; i++) {
        if (field[i] == -1) continue; // skip mines

        for (short j = -1; j <= 1; j++) {
            if (i + j >= 0 && i + j < size && field[i + j] == -1) {
                field[i]++; // increment count for adjacent mines
            }
        }
    }
}

void Game1D(int userId) {
    srand(time(NULL));

    short size = 0; // size of the field
    short *field = new short[size]; // 1D array for the field
    short mines = 0; // number of mines

    char dificulties[2][50] = {
        "1. Demo",
        "2. Custom"
    };

    bool total_exit = false; // Flag to exit the game loop
    while (!total_exit) {
        system("cls");
        cout << "Choose difficulty level:" << endl;
        Menu(dificulties, 2);
        int choice;
        cin >> choice;

        bool end = false;
        switch (choice) {
            case 1:
                size = 10; // Demo
                mines = 3;
                break;
            case 2:
                system("cls");
                while (!end) {
                    cout << "Enter custom size: ";
                    cin >> size;
                    cout << "Enter number of mines: ";
                    cin >> mines;
                    if (mines >= size) {
                        cout << "Number of mines cannot be greater than or equal to the size of the field." << endl;
                        system("pause");
                        continue; // Retry input
                    } else if (size <= 0 || mines < 0) {
                        cout << "Size and number of mines must be positive." << endl;
                        system("pause");
                        continue; // Retry input
                    } else if (mines == 0) {
                        cout << "Number of mines cannot be zero." << endl;
                        system("pause");
                        continue; // Retry input
                    }
                    end = true; // Valid input, exit loop
                }
                break;
            default:
                cout << "Invalid choice. Exiting game." << endl;
                return;
        }
        initField(field, size, mines); // Initialize the field with mines and counts

        // Game logic goes here...
    }
    delete[] field; // free allocated memory
}
