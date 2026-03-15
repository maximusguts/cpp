#include "common_code.cpp"
#include "game_logic.cpp"

void initField(short **field, short size, short mines) {
    for (short i = 0; i < size; i++) {
        field[i] = new short[size]; // allocate memory for each row
        for (short j = 0; j < size; j++) {
            field[i][j] = 0; // initialize all cells to 0
        }
    }

    // Place mines randomly
    short rest_mines = mines; // Remaining mines to place
    while (rest_mines > 0)
    {
        short x = rand() % size;
        short y = rand() % size;

        if (field[x][y] == 0) { // Check if the cell is empty
            field[x][y] = -1; // -1 indicates a mine
            rest_mines--; // Decrease remaining mines
        } else {
            continue; // If not empty, skip to next iteration
        }
    }

    // Count adjacent mines
    for (short i = 0; i < size; i++) {
        for (short j = 0; j < size; j++) {
            if (field[i][j] == -1) continue; // skip mines

            for (short dx = -1; dx <= 1; dx++) {
                for (short dy = -1; dy <= 1; dy++) {
                    if (dx == 0 && dy == 0) continue; // skip the cell itself
                    short ni = i + dx, nj = j + dy;
                    if (ni >= 0 && ni < size && nj >= 0 && nj < size && field[ni][nj] == -1) {
                        field[i][j]++; // increment count for adjacent mines
                    }
                }
            }
        }
    }
}

void Game2D(int userId) {
    srand(time(NULL));

    short size = 0; // size of the field
    short **field = new short*[size]; // 1D array for the field
    short mines = 0; // number of mines

    char dificulties[4][50] = {
        "1. Beginner",
        "2. Intermediate",
        "3. Expert",
        "4. Custom"
    };

    for (short i = 0; i < size; i++) {
        field[i] = new short[size]; // allocate memory for each row
    }

    bool total_exit = false; // Flag to exit the game loop
    while (!total_exit) {
        system("cls");
        cout << "Choose difficulty level:" << endl;
        Menu(dificulties, 4);
        int choice;
        cin >> choice;

        bool end = false;
        switch (choice) {
            case 1:
                size = 10; // Beginner
                mines = CountMines_byDimensions(2, size);
                break;
            case 2:
                size = 20; // Intermediate
                mines = CountMines_byDimensions(2, size);
                break;
            case 3:
                size = 30; // Expert
                mines = CountMines_byDimensions(2, size);
                break;
            case 4:
                system("cls");
                while (!end) {
                    cout << "Enter custom size: ";
                    cin >> size;
                    cout << "Enter number of mines: ";
                    cin >> mines;
                    if (mines >= degree(size, 2) / 2) {
                        if (mines >= degree(size, 2)) {
                            cout << "Number of mines cannot be greater than or equal to the size of the field." << endl;
                        } else {
                            cout << "Number of mines cannot be greater than or equal to half the size^2 of the field." << endl;
                        }
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
