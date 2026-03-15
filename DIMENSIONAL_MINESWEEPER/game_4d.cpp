#include "common_code.cpp"
#include "game_logic.cpp"

void Game4D(int userId) {
    srand(time(NULL));

    char dificulties[5][50] = {
        "1. Beginner",
        "2. Intermediate",
        "3. Expert",
        "4. Custom",
        "5. Back"
    };

    bool main_game_exit = false; // Flag to exit the main game loop

    system("cls");
    cout << "Welcome to 4D Minesweeper. Please use full screen to termnal for better experience." << endl;
    cout << "You can use the arrow keys to navigate to a cell." << endl;
    cout << "When you press '1', the cell will be opened, if it is not flagged." << endl;
    // cout << "But if all neighboring cells that flaged equal to the number of mines, then all neighboring cells will be opened." << endl;
    cout << "Press '2' to flag and unflag a cell." << endl;
    cout << "Also you can use 'a', 'd' to move in 3D, and 'w', 's' to move in 4D." << endl;
    cout << "Press '0' to reset the selected cell to (0, 0)." << endl;
    cout << "Press 'e' to see more information about this kays." << endl;
    cout << "Press 'r' to change rendering field size." << endl;
    cout << "Press 'q' to exit the game." << endl;
    cout << "Warning:" << endl;
    system("pause");

    while (!total_exit) {
        system("cls");
        cout << "Choose difficulty level:" << endl;
        Menu(dificulties, 5);
        bool custom_exit = false;
        int choice;
        cin >> choice;

        bool end = false;
        switch (choice) {
            case 1:
                size = 5; // Beginner
                mines = CountMines_byDimensions(4, size);
                break;
            case 2:
                size = 7; // Intermediate
                mines = CountMines_byDimensions(4, size);
                break;
            case 3:
                size = 10; // Expert
                mines = CountMines_byDimensions(4, size);
                break;
            case 4:
                while (!end) {
                    system("cls");
                    cout << "Enter custom size (quit code: -193): ";
                    cin >> size;
                    char respond[5] = "";
                    cin.ignore();
                    if (size == -193) {
                        end = true;
                        custom_exit = true;
                        continue;
                    }
                    if (size > 40) {
                        if (size > 50) {
                            if (size > 70) {
                                if (size > 100) {
                                    cout << "Program not allowing values more than 100. (you choose " << size << ")" << endl;
                                    system("pause");
                                    continue;
                                } else {
                                    cout << "After 70, (you choose " << size << ") it can be take more than 1Gb of RAM memory, ARE YOU SURE? (N/y)" << endl;
                                    cin.getline(respond, 3);
                                    if (!(strcmp(respond, "y") == 0)) {
                                        continue;
                                    }
                                }
                            } else {
                                cout << "50 this is the maximum size, (you choose " << size << 
                                        ") if you take more, computer will calculating too long, are you sure? (N/y)" << endl;
                                cin.getline(respond, 3);
                                if (!(strcmp(respond, "y") == 0)) {
                                    continue;
                                }
                            }
                        } else {
                            cout << "more than 40 is big number, (you choose " << size << ") do you realy want? (Y/n)" << endl;
                            cin.getline(respond, 3);
                            if (strcmp(respond, "n") == 0) {
                                continue;
                            }
                        }
                    }
                    if (size < 3) {
                        cout << "Program not allowing values less than 3. (you choose " << size << ")" << endl;
                        system("pause");
                        continue;
                    }
                    cout << "Enter number of mines: ";
                    cin >> mines;
                    if (mines >= degree(size, 4) / 2) {
                        if (mines >= degree(size, 4)) {
                            cout << "Number of mines cannot be greater than or equal to the size of the field." << endl;
                        } else {
                            cout << "Number of mines cannot be greater than or equal to half the size^4 of the field." << endl;
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
            case 5:
                total_exit = true;
                custom_exit = true;
                break;
            default:
                cout << "Invalid choice. Exiting game." << endl;
                return;
        }
        int rest_mines = mines; // Remaining mines to place
        if (custom_exit) continue;
        field = allocateField(size); // 4D array for the field
        initField(field, size, mines); // Initialize the field with mines and counts

        short x = fieldData.selected4D[0];
        short y = fieldData.selected4D[1];
        short z = fieldData.selected4D[2];
        short w = fieldData.selected4D[3];

        int* cords_of_topLeft_corner = new int[2]{0, 0}; // Coordinates of the top-left corner for rendering
        bool game_over_request = true; // Flag to request game over
        bool debug_mode = false; // Debug mode flag
        while (!main_game_exit) {

            char play_more[5] = "";
            if (game_over && game_over_request) {
                loses_count++;
                system("cls");
                cout << "your game was over cause one or more mine was opened. Do you want play more? (Y/n)" << endl;
                cin.ignore();
                cin.getline(play_more, 3);
                if (strcmp(play_more, "n")) {
                    OpenAllMines(field, size, fieldData, 4); // Open all mines
                    DelRecurringOpenedCells(fieldData, 4); // Remove recurring opened cells
                    game_over_request = false;
                    continue;
                } else {
                    DelOpenedCell(fieldData, 4, fieldData.selected4D[0], fieldData.selected4D[1], fieldData.selected4D[2], fieldData.selected4D[3]);
                    AddFlaggedCell(fieldData, 4, fieldData.selected4D[0], fieldData.selected4D[1], fieldData.selected4D[2], fieldData.selected4D[3]);
                    // Flag the mine that caused the game over
                    game_over = false;
                    continue;
                }
                system("pause");
            }
            if (degree(size, 4) - mines == fieldData.opened_count) {
                system("cls");
                game_won = true;
                PinAllFlags(field, size, fieldData, 4);
                cout << "Congratulations! You have been won." << endl;
                system("pause");
                continue;
            }
            if (rand() % 100 == 1) { // Randomly change the direction
                DelRecurringFlaggedCells(fieldData, 4); // Remove recurring flagged cells
                DelRecurringOpenedCells(fieldData, 4); // Remove recurring opened cells
            }

            system("cls");
            GetTopLeftCornerCords(fieldData, cords_of_topLeft_corner, screen_size, 4, 1); // Get the coordinates of the top-left corner for rendering
            Render_Field_2D(field[w][z], size, fieldData, cords_of_topLeft_corner, 4, screen_size, z, w); // Render the 2D field
            cout << "Your coordinates: (4D: " << w << ", 3D: " << z << ")" << " Your selected cell (in 2D): (y: " 
                 << y << ", x: " << x << ")" << endl;
            cout << "Remaining mines: " << rest_mines << endl;
            cout << "All mines: " << mines << endl;
            cout << "Number of losses: " << loses_count << endl << endl;
            PrintKayboard(keys, 4);
            
            keys.press_up = false;
            keys.press_down = false;
            keys.press_left = false;
            keys.press_right = false;
            keys.press_q = false;
            keys.press_w = false;
            keys.press_e = false;
            keys.press_r = false;
            keys.press_a = false;
            keys.press_s = false;
            keys.press_d = false;
            keys.press_0 = false;
            keys.press_1 = false;
            keys.press_2 = false;

            dir = STOP;
            dir2 = STOP;

            if (_kbhit()) {
                int ch = _getch();
                int ext = -1;
                if (ch == 0 || ch == 224) {
                    ext = _getch(); // second byte of arrow/function key
                }

                // Handle arrow keys for movement
                if (ext != -1) {
                    // arrows
                    switch (ext) {
                        case 72: dir = UP;    keys.press_up = true;    break; // ↑
                        case 80: dir = DOWN;  keys.press_down = true;  break; // ↓
                        case 75: dir = LEFT;  keys.press_left = true;  break; // ←
                        case 77: dir = RIGHT; keys.press_right = true; break; // →
                    }
                } else {
                    // ordinary kays
                    switch (ch) {
                        case 'q': case 'Q': keys.press_q = true;
                        cout << "check" << endl;
                        Exit_request(main_game_exit);
                        break;

                        case 'w': case 'W': keys.press_w = true; dir2 = UP_4D;    break; // Move up in 4D
                        case 'a': case 'A': keys.press_a = true; dir2 = LEFT_3D;  break; // Move left in 3D
                        case 's': case 'S': keys.press_s = true; dir2 = DOWN_4D;  break; // Move down in 4D
                        case 'd': case 'D': keys.press_d = true; dir2 = RIGHT_3D; break; // Move right in 3D
                        case '1':           keys.press_1 = true;
                        // Right click (to open the current cell)
                        if (game_over || game_won) continue;
                        if ((x < 0 || y < 0 || z < 0 || w < 0 || x >= size || y >= size || z >= size || w >= size) || 
                            fieldData.selected4D == nullptr || fieldData.pastSelected4D == nullptr) {
                                system("cls");
                                cout << "You are trying to open a cell outside the field, or something else. " <<
                                        "Please press any button, while we will reboot selected cells..." << endl;
                                system("pause");
                                if (fieldData.selected4D == nullptr) {
                                    fieldData.selected4D = new int[4]{0, 0, 0, 0}; // Initialize selected cell if it is null
                                } if (fieldData.pastSelected4D == nullptr) {
                                    fieldData.pastSelected4D = new int[4]{0, 0, 0, 0}; // Initialize previous selected cell if it is null
                                }
                                for (int i = 0; i < 4; i++) {
                                    fieldData.selected4D[i] = 0; // Reset selected cell to (0, 0, 0, 0)
                                    fieldData.pastSelected4D[i] = 0; // Reset previous selected cell to (0, 0, 0, 0)
                                }
                                continue; // Skip the rest of the loop and redraw the field
                        } else {
                            if (isOpened(fieldData, 4, x, y, z, w)) {
                                if (-1 != field[w][z][y][x] != 0 && 
                                    CountMinesAroundCell(field, size, x, y, z, w) - CountFlagedCellsAroundCell(fieldData, field, size, x, y, z, w) == 0) {
                                    game_over = OpenAllAroundCells_ExeptFlagedCells(fieldData, field, size, x, y, z, w);
                                    continue; // Continue opening surrounding cells
                                } else {
                                    continue; // Skip opening if cell is already opened and not indicating a number of mines around
                                }
                            } else if (isFlagged(fieldData, 4, x, y, z, w)) {
                                continue; // Skip opening if cell is flagged
                            } else {
                                if (field[w][z][y][x] == 0) RecursiveOpenCells(fieldData, field, size, x, y, z, w); // Open the cell recursively
                                else AddOpenedCell(fieldData, 4, size, x, y, z, w); // Open the cell
                            }
                            if (field[w][z][y][x] == -1) {
                                AddOpenedCell(fieldData, 4, size, x, y, z, w);
                                game_over = true; // Game over if a mine is opened
                            }

                        }
                        break;
                        case '2': keys.press_2 = true;
                        // Left click (to flag the current cell)
                        if (game_over || game_won) continue;
                        if (isOpened(fieldData, 4, x, y, z, w)) {
                            continue; // Skip flagging if cell is already opened
                        } else if (isFlagged(fieldData, 4, x, y, z, w)) {
                            DelFlaggedCell(fieldData, 4, x, y, z, w);
                            rest_mines++; // Increase remaining mines count
                        } else if (rest_mines > 0) {
                            AddFlaggedCell(fieldData, 4, size, x, y, z, w);
                            rest_mines--; // Decrease remaining mines count
                        }
                        break;
                        case '0': keys.press_0 = true; ChangeSelectedCell(fieldData, 4, 0, 0, 0, 0); break; // Set selected cords to {0, 0, 0, 0}
                        case 'e': case 'E': keys.press_e = true; system("cls"); ShowMoreInfo(4); break;
                        case 'r': case 'R': keys.press_r = true;
                        system("cls");
                        cout << "Enter new size of screen (field):" << endl;
                        cin >> screen_size;
                        cin.ignore(max(), '\n');
                        break;
                    }
                }
            }
            if (dir != STOP) {
                // sleep_for(milliseconds(400));
                if (dir == UP && y > 0) y--;
                if (dir == DOWN && y < size - 1) y++;
                if (dir == LEFT && x > 0) x--;
                if (dir == RIGHT && x < size - 1) x++;
            }
            if (dir2 != STOP) {
                // sleep_for(milliseconds(400));
                // cout << "check" << endl;
                if (dir2 == UP_4D && w > 0) w--;
                if (dir2 == DOWN_4D && w < size - 1) w++;
                if (dir2 == LEFT_3D && z > 0) z--;
                if (dir2 == RIGHT_3D && z < size - 1) z++;
            }

            sleep_for(milliseconds(16)); // Sleep for 16 milliseconds to control game speed ~60 FPS
        }
        delete[] cords_of_topLeft_corner;
        ArrayUsers au;
        au = {nullptr, 0, 0, 10};
        if (main_game_exit) {
            if (game_won) {
                GiveTotalPrizesToUser(userId, 4, loses_count, size, mines);
            } else {
                Load_Users_Data(au);
                int pos = Get_position_of_user(au, userId);
                system("cls");
                cout << "Good game " << au.ptrUs[pos]->username << ". Come back again!" << endl;
                system("pause");
            }
            game_over = false;
            game_won = false;
        }
    }
    FreeFieldData(fieldData); // Free allocated memory for field data
    for (short i = 0; i < size; i++) {
        for (short j = 0; j < size; j++) {
            for (short k = 0; k < size; k++) {
                delete[] field[i][j][k];
            }
            delete[] field[i][j];
        }
        delete[] field[i];
    }
    delete[] field; // free allocated memory
}

int main() {
    Game4D(687);
    return 1;
}
