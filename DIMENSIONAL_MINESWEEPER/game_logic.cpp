#pragma once
#include "common_code.cpp"

using namespace std::this_thread;
using namespace std::chrono;

template <typename T>
T degree(T x, int y) {
    T result = 1;
    if (y < 0) {
        x = 1 / x;
        y = -y;
    }

    for (int i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}

// template <typename T>
// T tetration(T x, int y) {
//     T result = 1;
//     if (y < 0) {
//         for (int i = -1; i > y; i--) {
//             degree();
//         }
//     }
// }

double Randint(int min, int max, int frction_step = 1) {
    if (min > max) {
        double temp = min;
        min = max;
        max = temp;
    }
    return (min*frction_step + rand() % int(max*frction_step - min*frction_step + 1)) / frction_step; // Generate a random integer between min and max in 1/step
}

long long max() {
    return 9223372036854775807;
}

bool GAME_OVER = false;
bool GAME_WON = false;
int OPENED_COUNT = 0; // Count of opened cells
int FLAGGED_COUNT = 0; // Count of flagged cells
bool MAIN_GAME_EXIT = false; // Flag to exit the main game loop

enum Directions {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    LEFT_3D,
    RIGHT_3D,
    UP_4D,
    DOWN_4D,
    STOP
};

class Cell {
public:
    bool is_mine = false; // Is there a mine in the cell
    bool is_opened = false; // Is the cell opened
    bool is_flagged = false; // Is the cell flagged
    int neighboring_mines = 0; // Number of neighboring mines
    int index[4] = {0, 0, 0, 0}; // Index of the cell in 4D space (for 2D and 3D, unused dimensions are set to 0)

    void reset() {
        is_mine = false;
        is_opened = false;
        is_flagged = false;
        neighboring_mines = 0;
    }

    void placeMine() {
        is_mine = true;
    }

    void open() {
        if (is_flagged) {
            if (is_opened) is_flagged = false;
        }
        is_opened = true;
        if (is_mine) GAME_OVER = true;
    }

    void toggleFlag() {
        if (is_opened) {
            is_flagged = false;
            return;
        }
        is_flagged = !is_flagged;
    }

    void setNeighboringMines(int count) {
        neighboring_mines = count;
    }

    void setIndex(int x, int y = 0, int z = 0, int w = 0) {
        index[0] = x;
        index[1] = y;
        index[2] = z;
        index[3] = w;
    }
};

class Field {
private:
    const char Cells_2D_USUAL_CELL[5][12] = {
        "###########",
        "##~~~~~~~##",
        "##~~~~~~~##",
        "##~~~~~~~##",
        "###########"
    };

    const char Cells_2D_USUAL_CELL_SELECTED[5][12] = {
        "```````````",
        ":#~~~~~~~#:",
        ":#~~~~~~~#:",
        ":#~~~~~~~#:",
        ",,,,,,,,,,,"
    };

    const char Cells_2D_USUAL_CELL_FLAG_PINED[5][12] = {
        "###########",
        "#~ /***| ~#",
        "#~ \\***| ~#",
        "#~~~~~ | ~#",
        "###########"
    };

    const char Cells_2D_USUAL_CELL_FLAG_PINED_SELECTED[5][12] = {
        "```````````",
        ":  /***|  :",
        ":  \\***|  :",
        ":      |  :",
        ",,,,,,,,,,,"
    };

    const char Cells_2D_OPENED_CELL[5][12] = {
        "```````````",
        ":         :",
        ":         :",
        ":         :",
        ",,,,,,,,,,,"
    };

    const char Cells_2D_OPENED_CELL_SELECTED[5][12] = {
        "###########",
        "#         #",
        "#         #",
        "#         #",
        "###########"
    };

    const char Cells_2D_OPENED_CELL_BOMB[5][12] = {
        "```````````",
        ":   # #   :",
        ":  #####  :",
        ":   # #   :",
        ",,,,,,,,,,,"
    };

    const char Cells_2D_OPENED_CELL_BOMB_SELECTED[5][12] = {
        "###########",
        "#   # #   #",
        "#  #####  #",
        "#   # #   #",
        "###########"
    };

    void Print_MiddleLine_OfCell_WithNumber(int number, bool bold = false) {
        short tens = number / 10;
        short units = number % 10;
        if (bold) {
            if (number < 0) {
                cout << "#   # #   #";
            } else if (number == 0) {
                cout << "#         #";
            } else {
                if (number < 10) {
                    cout << "#    " << number << "    #";
                } else if (number < 100) {
                    cout << "#   " << tens << " " << units << "   #";
                } else {
                    cout << "#         #";
                }
            }
        } else {
            if (number < 0) {
                cout << ":   # #   :";
            } else if (number == 0) {
                cout << ":         :";
            } else {
                if (number < 10) {
                    cout << ":    " << number << "    :";
                } else if (number < 100) {
                    cout << ":   " << tens << " " << units << "   :";
                } else {
                    cout << ":         :";
                }
            }
        }
    }
public:
    Cell* cells = nullptr; // Pointer to the array of cells
    int total_cells = 0; // Total number of cells in the field
    int mines = 0; // Total number of mines in the field
    int selected_cell_index[4] = {0, 0, 0, 0}; // Index of the currently selected cell in 4D space (for 2D and 3D, unused dimensions are set to 0)
    int* frame_cords = new int[2]{0, 0};
    int size[4] = {1, 1, 1, 1}; // Size of each dimension (for 2D and 3D, unused dimensions are set to 0)
    int size_int = 1;

    int Cords_to_integer(int x, int y = 0, int z = 0, int w = 0) {
        return x + y*size[0] + z*size[1]*size[0] + w*size[2]*size[1]*size[0];
    }

    int Cords_to_integer(int c[]) {
        return c[0] + c[1]*size[0] + c[2]*size[1]*size[0] + c[3]*size[2]*size[1]*size[0];
    }

    Cell& getCell(int x, int y = 0, int z = 0, int w = 0) {
        return cells[Cords_to_integer(x, y, z, w)]; // Calculate index for 4D coordinates
    }

    Cell& getCell(int cords[]) {
        return cells[Cords_to_integer(cords[])]; // Calculate index for 4D coordinates
    }

    void resetSelectedCell() {
        selected_cell_index[0] = 0;
        selected_cell_index[1] = 0;
        selected_cell_index[2] = 0;
        selected_cell_index[3] = 0;
    }

    void placeMines(int mine_count) {
        if (mine_count > total_cells/3) {
            mine_count = total_cells/3; // Limit mines to one-third of total cells for performance
        }
        // mines = mine_count;
        int placed_mines = 0;
        while (placed_mines < mine_count) {
            int index = Randint(0, total_cells - 1);
            if (!cells[index].is_mine) {
                cells[index].placeMine();
                placed_mines++;
            }
        }
    }

    void countNeighboringMines() {
        for (int i = 0; i < total_cells; i++) {
            if (cells[i].is_mine) continue;

            int count = 0;
            int x = cells[i].index[0];
            int y = cells[i].index[1];
            int z = cells[i].index[2];
            int w = cells[i].index[3];

            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dz = -1; dz <= 1; dz++) {
                        for (int dw = -1; dw <= 1; dw++) {
                            if (dx == 0 && dy == 0 && dz == 0 && dw == 0) continue;
                            int nx = x + dx;
                            int ny = y + dy;
                            int nz = z + dz;
                            int nw = w + dw;

                            if (nx >= 0 && nx < size[0] &&
                                ny >= 0 && ny < size[1] &&
                                nz >= 0 && nz < size[2] &&
                                nw >= 0 && nw < size[3]) {
                                int neighbor_index = nx + size[0] * (ny + size[1] * (nz + size[2] * nw));
                                if (cells[neighbor_index].is_mine) {
                                    count++;
                                }
                            }
                        }
                    }
                }
            }
            cells[i].setNeighboringMines(count);
        }
    }

    Field(int s[], int m, int d) : mines(m), size_int(s[0]) {
        // mines = m;
        for (int i = 0; i < d; i++) {
            size[i] = s[i]; // Set size for each dimension
        }
        total_cells = size[0]*size[1]*size[2]*size[3]; // Calculate total number of cells for 4D field
        cells = new Cell[total_cells]; // Allocate memory for cells

        // Initialize cell indices
        for (int i = 0; i < total_cells; i++) {
            int x = i % size[0];
            int y = (i / size[0]) % size[1];
            int z = (i / (size[0] * size[1])) % size[2];
            int w = (i / (size[0] * size[1] * size[2])) % size[3];
            cells[i].setIndex(x, y, z, w);
        }

        resetSelectedCell();
        placeMines(mines); // Place mines in the field
        countNeighboringMines(); // Count neighboring mines for each cell
    }

    ~Field() {
        delete[] cells; // Free allocated memory
    }

    void reset() {
        for (int i = 0; i < total_cells; i++) {
            cells[i].reset();
        }
        // opened_count = 0;
        // flagged_count = 0;
    }

    void move(Directions dir1, Directions dir2) {
        switch (dir1) {
            case RIGHT:
                if (selected_cell_index[0] < size[0] - 1) selected_cell_index[0]++;
                break;
            case LEFT:
                if (selected_cell_index[0] > 0) selected_cell_index[0]--;
                break;
            case UP:
                if (selected_cell_index[1] > 0) selected_cell_index[1]--;
                break;
            case DOWN:
                if (selected_cell_index[1] < size[1] - 1) selected_cell_index[1]++;
                break;
        } switch (dir2) {
            case RIGHT_3D:
                if (selected_cell_index[2] < size[2] - 1) selected_cell_index[2]++;
                break;
            case LEFT_3D:
                if (selected_cell_index[2] > 0) selected_cell_index[2]--;
                break;
            case UP_4D:
                if (selected_cell_index[3] > 0) selected_cell_index[3]--;
                break;
            case DOWN_4D:
                if (selected_cell_index[3] < size[3] - 1) selected_cell_index[3]++;
                break;
            case STOP:
                // Do nothing
                break;
        }
    }

    void ChangeSelectedCell(int x, int y = 0, int z = 0, int w = 0) {
        if (x >= 0 && x < size[0]) selected_cell_index[0] = x;
        if (y >= 0 && y < size[1]) selected_cell_index[1] = y;
        if (z >= 0 && z < size[2]) selected_cell_index[2] = z;
        if (w >= 0 && w < size[3]) selected_cell_index[3] = w;
    }

    void recurciveOpen(int x, int y = 0, int z = 0, int w = 0) {
        if (x < 0 || x >= size[0] || y < 0 || y >= size[1] ||
            z < 0 || z >= size[2] || w < 0 || w >= size[3]) return;
        Cell& cell = getCell(x, y, z, w);
        if (cell.is_opened || cell.is_flagged) return; // Base case: already opened or flagged
        cell.open();
        OPENED_COUNT++;

        // If the cell has no neighboring mines, recursively open its neighbors
        if (cell.neighboring_mines == 0) {
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dz = -1; dz <= 1; dz++) {
                        for (int dw = -1; dw <= 1; dw++) {
                            if (dx == 0 && dy == 0 && dz == 0 && dw == 0) continue; // Skip the current cell

                            // Mixing cordinates with vectors
                            int nx = x + dx;
                            int ny = y + dy;
                            int nz = z + dz;
                            int nw = w + dw;

                            // Check bounds and recurse
                            if (nx >= 0 && nx < size[0] &&
                                ny >= 0 && ny < size[1] &&
                                nz >= 0 && nz < size[2] &&
                                nw >= 0 && nw < size[3]) {
                                recurciveOpen(nx, ny, nz, nw);
                            }
                        }
                    }
                }
            }
        }
    }

    void OpenSelectedCell() {
        int x = selected_cell_index[0];
        int y = selected_cell_index[1];
        int z = selected_cell_index[2];
        int w = selected_cell_index[3];

        Cell& cell = getCell(x, y, z, w);
        if (cell.is_flagged || cell.is_opened) return;

        cell.open();
        OPENED_COUNT++;

        if (cell.is_mine) {
            GAME_OVER = true;
            return;
        }

        recurciveOpen(x, y, z, w);

        // win check
        int opened_safe = 0;
        for (int i = 0; i < total_cells; i++) {
            if (cells[i].is_opened && !cells[i].is_mine) opened_safe++;
        }
        if (opened_safe == total_cells - mines) {
            GAME_WON = true;
        }
    }

    void ToggleFlagSelected() {
        int x = selected_cell_index[0];
        int y = selected_cell_index[1];
        int z = selected_cell_index[2];
        int w = selected_cell_index[3];

        Cell& cell = getCell(x, y, z, w);
        cell.toggleFlag();
    }

    void OpenAllMines() {
        for (int i = 0; i < total_cells; i++) {
            if (cells[i].is_mine)
                cells[i].is_opened = true;
        }
    }

    void FlagAllMines() {
        for (int i = 0; i < total_cells; i++) {
            if (cells[i].is_mine)
                cells[i].is_flagged = true;
        }
    }

    int selectedX = 0; // current selected cell X
    int selectedY = 0; // current selected cell Y

    // Calculate the top-left corner of the frame based on selection
    void UpdateFrameCoords(int *pastCords, int frame_size, int dimensions = 2, int border = 1) {
        int newCords[2] = {0, 0}; // Initialize new coordinates
        int freeZone_size = frame_size - 2 * border; // Calculate the size of the free zone

        if (dimensions == 1) {
            int freeZone[2] = {
                pastCords[0] + border, // Left x
                pastCords[0] + frame_size - border // Right x
            };
            if (selected_cell_index[0] < freeZone[0]) {
                newCords[0] = selected_cell_index[0] - border; // Move left
            } else if (selected_cell_index[0] > freeZone[1]) {
                newCords[0] = selected_cell_index[0] - freeZone_size; // Move right
            } else {
                newCords[0] = pastCords[0]; // Stay
            }
        } else { // local processing of 2D coordinates from any dimension
            int sel2D[2] = {selected_cell_index[0], selected_cell_index[1]};
            int freeZone[4] = {
                pastCords[0] + border, // Left
                pastCords[1] + border, // Top
                pastCords[0] + frame_size - border, // Right
                pastCords[1] + frame_size - border // Bottom
            }; // Check if the selected cell is within the free zone
            if (sel2D[0] <= freeZone[0]) {
                newCords[0] = sel2D[0] - border; // Move left
            } else if (sel2D[0] >= freeZone[2]) {
                newCords[0] = sel2D[0] - freeZone_size; // Move right
            } else {
                newCords[0] = pastCords[0]; // Stay
            }
            if (sel2D[1] <= freeZone[1]) {
                newCords[1] = sel2D[1] - border; // Move up
            } else if (sel2D[1] >= freeZone[3]) {
                newCords[1] = sel2D[1] - freeZone_size; // Move down
            } else {
                newCords[1] = pastCords[1]; // Stay
            }
        } // Update past coordinates
        pastCords[0] = newCords[0];
        if (dimensions > 1) {
            pastCords[1] = newCords[1];
        }
    }

    // and now, my favorite function in whole project (i wrote it by myself)
    void Render_Field_2D(int dimensions, int frame_size = 5) {
        // Render a 2D field with the given size and field data
        int rows = size;
        bool small_screen = false;
        if (dimensions == 1) {
            rows = 1; // For 1D Minesweeper, only one row is needed
        } if (frame_size < 6 || size < 6) {
            if (frame_size < 3) {
                frame_size = 3; // Ensure frame size is at least 3 for proper rendering
                small_screen = true;
            }
            small_screen = true;
            //because we`ll don`t see numbers of columns and rows
        }

        if (*frame_cords[0] < 0) {
            *frame_cords[0] = 0;
        } if (*frame_cords[0] > size - frame_size) {
            *frame_cords[0] = size - frame_size;
        } if (*frame_cords[1] < 0) {
            *frame_cords[1] = 0;
        } if (*frame_cords[1] > size - frame_size) {
            *frame_cords[1] = size - frame_size;
        }

        // Calculate the range of rows and cells to print based on the frame size and current coordinates
        int rows_to_print_start = (rows > frame_size) ? (*frame_cords[1] < rows - frame_size ? *frame_cords[1] : rows - frame_size) : 0;
        int rows_to_print_end = rows_to_print_start + frame_size < rows ? rows_to_print_start + frame_size : rows;
        int cells_to_print_start = (size > frame_size) ? (*frame_cords[0] < size - frame_size ? *frame_cords[0] : size - frame_size) : 0;
        int cells_to_print_end = cells_to_print_start + frame_size < size ? cells_to_print_start + frame_size : size;
        // Calculate the range of rows and cells to print based on the frame size and current coordinates

        if (rows_to_print_start < 0) rows_to_print_start = 0; // Ensure start row is not negative
        if (cells_to_print_start < 0) cells_to_print_start = 0; // Ensure start cell is not negative

        for (int line = 0; line < 5; line++) {
            for (int cell = cells_to_print_start - 1; cell < cells_to_print_end; cell++) {
                if (cell == cells_to_print_start - 1) {
                    cout << "           ";
                    continue; // Skip the first cell if it is -1
                }
                if (line == 2) {
                    if (small_screen) {
                        if (cell + 1 >= 100) { // Print cell number without padding
                            cout << "    " << cell + 1 << "    "; // Print cell number more than 99 without padding    
                        } else if (cell + 1 > 10) {
                            short tens = (cell + 1) / 10;
                            short units = (cell + 1) % 10;
                            cout << "    " << tens << " " << units << "    "; // Print cell number more than 9 without padding
                        } else {
                            cout << "     " << cell + 1 << "     "; // Print cell number less than 10 without padding
                        }
                    } else {
                        if ((cell + 1) % 10 == 0 || cell == 0) { // Print cell number with padding
                            if (cell + 1 >= 100) {
                                cout << "  # " << cell + 1 << " #  "; // Print cell number more than 99 with padding    
                            } else if (cell + 1 > 10) {
                                short tens = (cell + 1) / 10;
                                short units = (cell + 1) % 10;
                                cout << "  # " << tens << " " << units << " #  "; // Print cell number more than 9 with padding
                            } else {
                                cout << "   # " << cell + 1 << " #   "; // Print cell number less than 10 with padding
                            }
                        } else if ((cell + 1) % 5 == 0) { // Print cell number without padding
                            if (cell + 1 >= 100) {
                                cout << "    " << cell + 1 << "    "; // Print cell number more than 99 without padding    
                            } else if (cell + 1 > 10) {
                                short tens = (cell + 1) / 10;
                                short units = (cell + 1) % 10;
                                cout << "    " << tens << " " << units << "    "; // Print cell number more than 9 without padding
                            } else {
                                cout << "     " << cell + 1 << "     "; // Print cell number less than 10 without padding
                            }
                        } else {
                            cout << "     |     "; // Print cell without number
                        }
                    }
                } else if (line == 1 || line == 3) {
                    cout << "     |     "; // Print cell without number
                }
                if (cell != cells_to_print_end - 1) {
                    cout << "  "; // Space between cells
                }
            }
            cout << endl; // New line after each line of cells
        }

        for (int row = rows_to_print_start; row < rows_to_print_end; row++) {
            for (int line = 0; line < 5; line++) {
                for (int cell = cells_to_print_start - 1; cell < cells_to_print_end; cell++) {
                    if (cell == cells_to_print_start - 1) {
                        if (line == 2) {
                            if (small_screen) {
                                if (row + 1 >= 100) { // Print row number without padding
                                    cout << " -- " << row + 1 << " -- "; // Print row number more than 99 without padding    
                                } else if (row + 1 >= 10) {
                                    short tens = (row + 1) / 10;
                                    short units = (row + 1) % 10;
                                    cout << " -- " << tens << " " << units << " -- "; // Print row number more than 9 without padding
                                } else {
                                    cout << " --- " << row + 1 << " --- "; // Print row number less than 10 without padding
                                }
                            } else {
                                if ((row + 1) % 10 == 0 || row == 0) { // Print row number with padding
                                    if (row + 1 >= 100) {
                                        cout << " -# " << row + 1 << " #- "; // Print row number more than 99 with padding    
                                    } else if (row + 1 >= 10) {
                                        short tens = (row + 1) / 10;
                                        short units = (row + 1) % 10;
                                        cout << " -# " << tens << " " << units << " #- "; // Print row number more than 9 with padding
                                    } else {
                                        cout << " --# " << row + 1 << " #-- "; // Print row number less than 10 with padding
                                    }
                                } else if ((row + 1) % 5 == 0) { // Print row number without padding
                                    if (row + 1 >= 100) {
                                        cout << " -- " << row + 1 << " -- "; // Print row number more than 99 without padding    
                                    } else if (row + 1 > 10) {
                                        short tens = (row + 1) / 10;
                                        short units = (row + 1) % 10;
                                        cout << " -- " << tens << " " << units << " -- "; // Print row number more than 9 without padding
                                    } else {
                                        cout << " --- " << row + 1 << " --- "; // Print row number less than 10 without padding
                                    }
                                } else {
                                    cout << "   -----   "; // Print row without number
                                }
                            }
                        } else {
                            cout << "           ";
                            continue; // Skip the empty column
                        }
                        continue;
                    }
                    if (selected_cell_index[0] == cell && selected_cell_index[1] == row) {
                        if (cells[Cords_to_integer(selected_cell_index)].is_flagged) { // Check if the cell is flagged
                            cout << Cells_2D_USUAL_CELL_FLAG_PINED_SELECTED[line];
                        } else if (cells[Cords_to_integer(selected_cell_index)].is_opened) { // Check if the cell is opened
                            cout << Cells_2D_OPENED_CELL_BOMB_SELECTED[line];
                        } else { // If cell is not flagged, and opened, printing usual selected cell
                            cout << Cells_2D_USUAL_CELL_SELECTED[line];
                        }
                    } else {
                        if (cells[Cords_to_integer(selected_cell_index)].is_flagged) { // Check if the cell is flagged
                            cout << Cells_2D_USUAL_CELL_FLAG_PINED[line];
                        } else if (cells[Cords_to_integer(selected_cell_index)].is_opened) { // Check if the cell is opened
                            cout << Cells_2D_OPENED_CELL_BOMB[line];
                        } else { // If cell is not flagged, and opened, printing usual cell
                            cout << Cells_2D_USUAL_CELL[line];
                        }
                    }
                    if (cell < cells_to_print_end - 1) {
                        cout << "  "; // Space between cells
                    } else {
                        cout << endl; // New line after each row
                    }
                }
            }
            if (row < rows_to_print_end - 1) {
                cout << endl; // New line after each row
            }
        }
    }

    // bool isWin() const { return OPENED_COUNT == total_cells - mines; }
};

struct KeysData {
    bool press_1 = false;
    bool press_2 = false;
    bool press_0 = false;
    bool press_q = false;
    bool press_w = false;
    bool press_e = false;
    bool press_r = false;
    bool press_a = false;
    bool press_s = false;
    bool press_d = false;
    bool press_up = false;
    bool press_left = false;
    bool press_down = false;
    bool press_right = false;
};

class Game {
private:
    Field* field = nullptr;
    KeysData keys;
    Directions dir = STOP; // Direction of movement
    Directions dir2 = STOP; // Direction of movement (3D, 4D)
    bool exit_requested = false;
    bool local_game_over = false;

    int dimensions;
    int size[4] = {1, 1, 1, 1};
    int mine_count;

    bool exit_flag = false;
    short loses_count = 0; // Count of defeated games
    bool total_exit = false; // Flag to exit the game loop

    int x = 0;
    int y = 0;
    int z = 0;
    int w = 0;

public:
    int CountMines_byDimensions(int dimensions, int size) {
        if (dimensions < 1 || size < 1) {
            return 0; // Invalid dimensions or size
        }

        int mines = 0;
        switch (dimensions) {
            case 1:
                mines = Randint(size / 6, size / 3); // 1D Minesweeper
                break;
            case 2:
                mines = Randint(degree(size, 2) / 4, degree(size, 2) / 3); // 2D Minesweeper
                break;
            case 3:
                mines = Randint(degree(size, 3) / 10, degree(size, 3) / 8); // 3D Minesweeper
                break;
            case 4:
                mines = Randint(degree(size, 4) / 30, degree(size, 4) / 25); // 4D Minesweeper
                break;
            default:
                mines = Randint(size / 1.5, size); // Default case for unsupported dimensions
        }
        return mines;
    }

    Game(int dims, int field_size) : dimensions(dims) {
        for (int i = 0; i < dims; i++) size[i] = field_size;

        // Count mines based on field size and dimensionality
        mine_count = CountMines_byDimensions(dimensions, field_size);

        // Create field (assumes Field constructor accepts size[], mine_count, dimensions)
        field = new Field(size, mine_count, dimensions);
    }

    ~Game() {
        delete field;
    }

    void PrintKayboard(const KeysData kaysData) {
        cout << "KayBoard REFERENCE (actual kays)" << endl << endl;
        cout << "   " << (kaysData.press_1 == true ? "# " : "1 ") << (kaysData.press_2 == true ? "#" : "2") << 
                "        " << (kaysData.press_0 == true ? "#" : "0") << endl;
        cout << "    " << (kaysData.press_q == true ? "# " : "q ") << 
                (dimensions != 4 ? "  " : (kaysData.press_w == true ? "# " : "w ")) << 
                (kaysData.press_e == true ? "# " : "e ") << (kaysData.press_r == true ? "# " : "r ") << endl;
        cout << "    " << (dimensions < 3 ? "  " : (kaysData.press_a == true ? "# " : "a ")) << 
                (dimensions != 4 ? "  " : (kaysData.press_s == true ? "# " : "s ")) << 
                (dimensions < 3 ? "  " : (kaysData.press_d == true ? "# " : "d ")) << "          " << 
                (dimensions < 2 ? "  " : (kaysData.press_up == true ? "# " : "^ ")) << endl;
        cout << "                  " << (kaysData.press_left == true ? "# " : "< ") << 
                (dimensions < 2 ? "  " : (kaysData.press_down == true ? "# " : "- ")) << 
                (kaysData.press_right == true ? "#" : ">") << endl << endl;
    }

    void ShowMoreInfo(short dimensions) {
        cout << "1. Numbers" << endl;
        cout << "\t1 - Working like a normal left click on mouth." << endl;
        cout << "\t\tIt's opening a cell if it's not flaged." << endl;
        cout << "\t\tBut if all neighboring cells that flaged equal to the number of neighboring mines, then all neighboring cells will be opened." << endl << endl;

        cout << "\t2 - Working like a normal right click on mouth." << endl;
        cout << "\t\tIf you press '2' when you selected a un-opened cell, it will be flaged." << endl;
        cout << "\t\tAnd if you press '2' when you selected a flaged cell, it will be un-flaged." << endl;
        cout << "\t\tBut when you try press '2' when cell is opened, nothing will hapend." << endl << endl;

        cout << "\t0 - Just send you to zero coordinates. (start of the whole field)" << endl;
        if (dimensions == 3) {
            cout << "\t\tIt's also works to a 3-rd dimension" << endl << endl << endl;
        } else if (dimensions == 4) {
            cout << "\t\tIt's also works to a 3-rd, and 4-th dimension" << endl << endl << endl;
        }

        cout << "2. Letters" << endl;
        cout << "\tQ - quit. sending yourself to a menu." << endl;
        cout << "\t\tAlso, after pressing 'q', program asking you if you're ready." << endl << endl;

        cout << "\tE - Showing more information about alowed kays on kayboard." << endl << endl;

        cout << "\tR - After pressing 'R', you can enter new size of visible field." << endl;
        cout << "\t\tIt's working like zoom in/zoom out without proportion." << endl;
        cout << "\t\tAlso, this function written for nice view on big fields." << endl;
        cout << "\t\tBut if you enter size less than 3, it will be setted to 3." << endl;
        cout << "\t\tAnd recommended size is from 4 to 6." << endl << endl;

        if (dimensions >= 3) {
            cout << "\tA - Moves you by back direction in 3D." << endl;
            cout << "\t\tTo be more precise, you just moving by left direction in (1-st - if it's 3-rd, and 2-nd - if it's 4-th dimension)" << endl;
            cout << "\t\tdimension of 2-nd dimensions (More about this in (MainMenu) -> (2. Show Instructions))" << endl << endl;

            cout << "\tD - Working like 'A' but moves you by forvard direction in 3D." << endl;
            cout << "\t\tIt also just moving you (not by left) by right direction in (1-st - if it's 3-rd, and 2-nd - if it's 4-th dimension)" << endl;
            cout << "\t\tdimension of 2-nd dimensions (More about this in (MainMenu) -> (2. Show Instructions))" << endl << endl;
        } if (dimensions == 4) {
            cout << "\tS - Absolutly doing same as 'A' but in 4D." << endl << endl;

            cout << "\tW - Also doing same as 'D' but in 4D" << endl << endl;
        }
        cout << endl;
        
        cout << "3. Arrows" << endl;
        cout << "\t< - Moves to left" << endl;
        cout << "\t> - Moves to right" << endl;
        if (dimensions != 1) {
            cout << "\t^ - Moves to up" << endl;
            cout << "\t\\/ - Moves to down" << endl;
        }
        cout << endl << endl;
        system("pause");
    }

    void ExitRequest() {
        system("cls");
        cout << "Are you sure you want to quit? (Y/n): ";

        int ans = _getch(); // Single key input without echo
        if (ans == 'n' || ans == 'N') {
            exit_flag = false;
        } else {
            exit_flag = true;
        }
    }

    bool ShouldExit() const {
        return exit_flag;
    }

    bool AllMinesFlagged() const {
        if (FLAGGED_COUNT != field) return false;
        bool yes = true;
        for (int i = 0; i < 0; i++) {
            if (field->cells[i].is_mine && !field->cells[i].is_flagged) yes = false;
        }
        return yes;
    }

    int CountAroundCell(srting state, int x, int y = 0, int z = 0, int w = 0) {
        int count = 0;
        if (dimensions = 1) {
            for (int dx = -1; dx <= 1; dx++) {
                if (dx == 0) continue; // Skip the cell itself
                if (dx+x < 0 || dx+x > size[0]) continue; // skip if it out of field
                if (state == "mine") {
                    if (field->cells[dx+x].is_mine) count++;
                } else if (state == "flagged") {
                    if (field->cells[dx+x].is_flagged) count++;
                } else if (state == "opened") {
                    if (field->cells[dx+x].is_opened) count++;
                } else return 0;
            }
        } else if (dimensions = 2) {
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    if (dx == 0 && dy == 0) continue; // Skip the cell itself
                    if (dx+x < 0 || dx+x > size[0] 
                    || dy+y < 0 || dy+y > size[1])
                        continue; // skip if it out of field
                    if (state == "mine") {
                        if (field->cells[field->Cords_to_integer(dx+x, dy+y)].is_mine) count++;
                    } else if (state == "flagged") {
                        if (field->cells[field->Cords_to_integer(dx+x, dy+y)].is_flagged) count++;
                    } else if (state == "opened") {
                        if (field->cells[field->Cords_to_integer(dx+x, dy+y)].is_opened) count++;
                    } else return 0;
                }
            }
        } else if (dimensions = 3){
            for (int dz = -1; dz <= 1; dz++) {
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        if (dx == 0 && dy == 0 && dz == 0) continue; // Skip the cell itself
                        if (dx+x < 0 || dx+x > size[0] 
                        || dy+y < 0 || dy+y > size[1] 
                        || dz+z < 0 || dz+z > size[2])
                            continue; // skip if it out of field
                        if (state == "mine") {
                            if (field->cells[field->Cords_to_integer(dx+x, dy+y, dz+z)].is_mine) count++;
                        } else if (state == "flagged") {
                            if (field->cells[field->Cords_to_integer(dx+x, dy+y, dz+z)].is_flagged) count++;
                        } else if (state == "opened") {
                            if (field->cells[field->Cords_to_integer(dx+x, dy+y, dz+z)].is_opened) count++;
                        } else return 0;
                    }
                }
            }
        } else if (dimensions = 4) {
            for (int dw = -1; dw <= 1; dw++) {
                for (int dz = -1; dz <= 1; dz++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        for (int dx = -1; dx <= 1; dx++) {
                            if (dx == 0 && dy == 0 && dz == 0 && dw == 0) continue; // Skip the cell itself
                            if (dx+x < 0 || dx+x > size[0] 
                             || dy+y < 0 || dy+y > size[1] 
                             || dz+z < 0 || dz+z > size[2] 
                             || dw+w < 0 || dw+w > size[3])
                                continue; // skip if it out of field
                            if (state == "mine") {
                                if (field->cells[field->Cords_to_integer(dx+x, dy+y, dz+z, dw+w)].is_mine) count++;
                            } else if (state == "flagged") {
                                if (field->cells[field->Cords_to_integer(dx+x, dy+y, dz+z, dw+w)].is_flagged) count++;
                            } else if (state == "opened") {
                                if (field->cells[field->Cords_to_integer(dx+x, dy+y, dz+z, dw+w)].is_opened) count++;
                            } else return 0;
                        }
                    }
                }
            }
        }
        return count;
    }

    void ExeptingOpenAllAroundCells(string state, string exept, int x, int y = 0, int z = 0, int w = 0) {
        if (state == exept || state == "opened") return;
        int count = 0;
        if (dimensions = 1) {
            for (int dx = -1; dx <= 1; dx++) {
                if (dx == 0) continue; // Skip the cell itself
                if (dx+x < 0 || dx+x > size[0]) continue; // skip if it out of field
                if (state == "mine") {
                    if (field->cells[dx+x].is_mine) count++;
                } else if (state == "flagged") {
                    if (field->cells[dx+x].is_flagged) count++;
                } else if (state == "opened") {
                    if (field->cells[dx+x].is_opened) count++;
                } else return 0;
            }
        } else if (dimensions = 2) {
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    if (dx == 0 && dy == 0) continue; // Skip the cell itself
                    if (dx+x < 0 || dx+x > size[0] 
                    || dy+y < 0 || dy+y > size[1])
                        continue; // skip if it out of field
                    if (state == "mine") {
                        if (field->cells[field->Cords_to_integer(dx+x, dy+y)].is_mine) count++;
                    } else if (state == "flagged") {
                        if (field->cells[field->Cords_to_integer(dx+x, dy+y)].is_flagged) count++;
                    } else if (state == "opened") {
                        if (field->cells[field->Cords_to_integer(dx+x, dy+y)].is_opened) count++;
                    } else return 0;
                }
            }
        } else if (dimensions = 3){
            for (int dz = -1; dz <= 1; dz++) {
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        if (dx == 0 && dy == 0 && dz == 0) continue; // Skip the cell itself
                        if (dx+x < 0 || dx+x > size[0] 
                        || dy+y < 0 || dy+y > size[1] 
                        || dz+z < 0 || dz+z > size[2])
                            continue; // skip if it out of field
                        if (state == "mine") {
                            if (field->cells[field->Cords_to_integer(dx+x, dy+y, dz+z)].is_mine) count++;
                        } else if (state == "flagged") {
                            if (field->cells[field->Cords_to_integer(dx+x, dy+y, dz+z)].is_flagged) count++;
                        } else if (state == "opened") {
                            if (field->cells[field->Cords_to_integer(dx+x, dy+y, dz+z)].is_opened) count++;
                        } else return 0;
                    }
                }
            }
        } else if (dimensions = 4) {
            for (int dw = -1; dw <= 1; dw++) {
                for (int dz = -1; dz <= 1; dz++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        for (int dx = -1; dx <= 1; dx++) {
                            if (dx == 0 && dy == 0 && dz == 0 && dw == 0) continue; // Skip the cell itself
                            if (dx+x < 0 || dx+x > size[0] 
                             || dy+y < 0 || dy+y > size[1] 
                             || dz+z < 0 || dz+z > size[2] 
                             || dw+w < 0 || dw+w > size[3])
                                continue; // skip if it out of field
                            if (state == "mine") {
                                if (field->cells[field->Cords_to_integer(dx+x, dy+y, dz+z, dw+w)].is_mine) count++;
                            } else if (state == "flagged") {
                                if (field->cells[field->Cords_to_integer(dx+x, dy+y, dz+z, dw+w)].is_flagged) count++;
                            } else if (state == "opened") {
                                if (field->cells[field->Cords_to_integer(dx+x, dy+y, dz+z, dw+w)].is_opened) count++;
                            } else return 0;
                        }
                    }
                }
            }
        }
    }

    void Render(int frame_s) {
        field->UpdateFrameCoords(field->frame_cords, frame_s, dimensions);
        field->Render_Field_2D(dimensions, frame_s);
        cout << "Your coordinates: (4D: " << field->selected_cell_index[3] 
             << ", 3D: " << field->selected_cell_index[2] << ")" 
             << " Your selected cell (in 2D): (y: " << field->selected_cell_index[1] 
             << ", x: " << field->selected_cell_index[0] << ")" << endl;

        cout << "Remaining mines: " << field->mines-FLAGGED_COUNT << endl;
        cout << "All mines: " << field->mines << endl;
        cout << "Number of losses: " << loses_count << endl << endl;
        PrintKayboard(keys);
    }

    void Input() {
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
                    // cout << "check" << endl;
                    ExitRequest();
                    break;

                    case 'w': case 'W': keys.press_w = true; dir2 = UP_4D;    break; // Move up in 4D
                    case 'a': case 'A': keys.press_a = true; dir2 = LEFT_3D;  break; // Move left in 3D
                    case 's': case 'S': keys.press_s = true; dir2 = DOWN_4D;  break; // Move down in 4D
                    case 'd': case 'D': keys.press_d = true; dir2 = RIGHT_3D; break; // Move right in 3D
                    case '1':           keys.press_1 = true;
                    // Right click (to open the current cell)
                    if (GAME_OVER || GAME_WON) continue;
                    if (x < 0 || y < 0 || z < 0 || w < 0 || x >= size || y >= size || z >= size || w >= size) {
                        system("cls");
                        cout << "You are trying to open a cell outside the field, or something else. " <<
                                "Please press any button, while we will reboot selected cells..." << endl;
                        system("pause");
                        for (int i = 0; i < 4; i++) {
                            field->selected_cell_index[i] = 0; // Reset selected cell to (0, 0, 0, 0)
                        }
                        continue; // Skip the rest of the loop and redraw the field
                    } else {
                        if (field->cells[field->Cords_to_integer(x, y, z, w)].is_opened) {
                            if (!field->cells[field->Cords_to_integer(x, y, z, w)].is_mine && 
                                CountAroundCell("mine", x, y, z, w) - CountAroundCell("flagged", x, y, z, w) == 0) {
                                OpenAllAroundCells_ExeptFlagedCells(x, y, z, w);
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
    }

    void Update() {
        x = field->selected_cell_index[0];
        y = field->selected_cell_index[1];
        z = field->selected_cell_index[2];
        w = field->selected_cell_index[3];

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
    }

    void Run() {
        x = field->selected_cell_index[0];
        y = field->selected_cell_index[1];
        z = field->selected_cell_index[2];
        w = field->selected_cell_index[3];
        while (!MAIN_GAME_EXIT) {
            char play_more[5] = "";
            if (GAME_OVER && ShouldExit()) {
                loses_count++;
                system("cls");
                cout << "your game was over cause one or more mine was opened. Do you want play more? (Y/n)" << endl;
                cin.ignore();
                cin.getline(play_more, 3);
                if (strcmp(play_more, "n")) {
                    field->OpenAllMines(); // Open all mines
                    exit_flag = false;
                    continue;
                } else {
                    field->cells[field->Cords_to_integer(field->selected_cell_index)].is_opened = false;
                    field->cells[field->Cords_to_integer(field->selected_cell_index)].is_flagged = true;
                    // Flag the mine that caused the game over
                    GAME_OVER = false;
                    continue;
                }
                system("pause");
            }
            if (AllMinesFlagged() || field->total_cells - OPENED_COUNT == field->mines) {
                system("cls");
                GAME_WON = true;
                field->FlagAllMines();
                cout << "Congratulations! You have been won." << endl;
                system("pause");
                continue;
            }

            system("cls");
            Render();
            Input();
            Update();
            sleep_for(milliseconds(16)); // Sleep for 16 milliseconds to control game speed ~60 FPS
        }

        system("cls");
        if (GAME_OVER) {
            cout << "\nGame Over!\n";
        } else {
            cout << "\nExiting game...\n";
        }
    }
};

// ### 1D Minesweeper ###

void OpenAllMines(short *field, short size, FieldData& fieldData) {
    for (short i = 0; i < size; i++) {
        if (field[i] == -1) {
            AddOpenedCell(fieldData, 1, size, i); // Open the mine cell
        }
    }
}

void PinAllFlags(short *field, short size, FieldData& fieldData) {
    for (short i = 0; i < size; i++) {
        if (field[i] == -1) {
            AddFlaggedCell(fieldData, 1, size, i); // Flag the mine cell
        }
    }
}

int CountMinesAroundCell(short *field, short size, short x) {
    int count = 0;
    for (short i = -1; i <= 1; i++) {
        if (i == 0) continue; // Skip the cell itself
        short nx = x + i;
        if (nx >= 0 && nx < size && field[nx] == -1) {
            count++; // Increment count for adjacent mines
        }
    }
    return count;
}

int CountOpenedCellsAroundCell(FieldData& fieldData, short *field, short size, short x) {
    int count = 0;
    for (short i = -1; i <= 1; i++) {
        if (i == 0) continue; // Skip the cell itself
        short nx = x + i;
        if (nx >= 0 && nx < size && isOpened(fieldData, 1, nx)) { // If adjacent cell is opened
            count++; // Increment count
        }
    }
    return count;
}

int CountFlagedCellsAroundCell(FieldData& fieldData, short *field, short size, short x) {
    int count = 0;
    for (short i = -1; i <= 1; i++) {
        if (i == 0) continue; // Skip the cell itself
        short nx = x + i;
        if (nx >= 0 && nx < size && isFlagged(fieldData, 1, nx)) { // If adjacent cell is flagged
            count++; // Increment count
        }
    }
    return count;
}

bool OpenAllAroundCells_ExeptFlagedCells(FieldData& fieldData, short *field, short size, short x) {
    bool gameOver = false; // Flag to check if game is over
    for (short i = -1; i <= 1; i++) {
        if (i == 0) continue; // Skip the cell itself
        short nx = x + i;
        if (nx >= 0 && nx < size) {
            if (!isFlagged(fieldData, 1, nx) && !isOpened(fieldData, 1, nx)) {
                AddOpenedCell(fieldData, 1, size, nx);
                if (field[nx] == -1) {
                    gameOver = true; // Game over if a mine is opened
                }
            }
        }
    }
    return gameOver; // Return the game over status
}

void RecursiveOpenCells(FieldData& fieldData, short *field, short size, short x) {
    if (isOpened(fieldData, 1, x)) return; // If cell is already opened
    AddOpenedCell(fieldData, 1, size, x); // Open the cell

    int minesCount = CountMinesAroundCell(field, size, x);
    if (minesCount == 0) {
        for (short dx = -1; dx <= 1; dx++) {
            if (dx == 0) continue; // Skip the cell itself
            short nx = x + dx;
            if (nx >= 0 && nx < size) {
                RecursiveOpenCells(fieldData, field, size, nx); // Recursively open adjacent cells
            }
        }    
    }
}

// ### 2D Minesweeper ###

void OpenAllMines(short **field, short size, FieldData& fieldData) {
    for (short i = 0; i < size; i++) {
        for (short j = 0; j < size; j++) {
            if (field[i][j] == -1) {
                AddOpenedCell(fieldData, 2, size, i, j); // Open the mine cell
            }
        }
    }
}

void PinAllFlags(short **field, short size, FieldData& fieldData) {
    for (short i = 0; i < size; i++) {
        for (short j = 0; j < size; j++) {
            if (field[i][j] == -1) {
                AddFlaggedCell(fieldData, 2, size, i, j); // Flag the mine cell
            }
        }
    }
}

int CountMinesAroundCell(short **field, short size, short x, short y) {
    int count = 0;
    for (short dx = -1; dx <= 1; dx++) {
        for (short dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue; // Skip the cell itself
            short nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < size && ny >= 0 && ny < size && field[nx][ny] == -1) {
                count++; // Increment count for adjacent mines
            }
        }
    }
    return count;
}

int CountOpenedCellsAroundCell(FieldData& fieldData, short **field, short size, short x, short y) {
    int count = 0;
    for (short dx = -1; dx <= 1; dx++) {
        for (short dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue; // Skip the cell itself
            short nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < size && ny >= 0 && ny < size &&
                isOpened(fieldData, 2, nx, ny)) { // If adjacent cell is opened
                count++; // Increment count
            }
        }
    }
    return count;
}

int CountFlagedCellsAroundCell(FieldData& fieldData, short **field, short size, short x, short y) {
    int count = 0;
    for (short dx = -1; dx <= 1; dx++) {
        for (short dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue; // Skip the cell itself
            short nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < size && ny >= 0 && ny < size &&
                isFlagged(fieldData, 2, nx, ny)) { // If adjacent cell is flagged
                count++; // Increment count
            }
        }
    }
    return count;
}

bool OpenAllAroundCells_ExeptFlagedCells(FieldData& fieldData, short **field, short size, short x, short y) {
    bool gameOver = false; // Flag to check if game is over
    for (short dx = -1; dx <= 1; dx++) {
        for (short dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue; // Skip the cell itself
            short nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < size && ny >= 0 && ny < size) {
                if (!isFlagged(fieldData, 2, nx, ny) && !isOpened(fieldData, 2, nx, ny)) {
                    AddOpenedCell(fieldData, 2, size, nx, ny);
                    if (field[nx][ny] == -1) {
                        gameOver = true; // Game over if a mine is opened
                    }
                }
            }
        }
    }
    return gameOver; // Return the game over status
}

void RecursiveOpenCells(FieldData& fieldData, short **field, short size, short x, short y) {
    if (isOpened(fieldData, 2, x, y)) return; // If cell is already opened
    AddOpenedCell(fieldData, 2, size, x, y); // Open the cell

    int minesCount = CountMinesAroundCell(field, size, x, y);
    if (minesCount == 0) {
        for (short dx = -1; dx <= 1; dx++) {
            for (short dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue; // Skip the cell itself
                short nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < size && ny >= 0 && ny < size) {
                    RecursiveOpenCells(fieldData, field, size, nx, ny); // Recursively open adjacent cells
                }
            }
        }
    }
}

// ### 3D Minesweeper ###

void OpenAllMines(short ***field, short size, FieldData& fieldData) {
    for (short i = 0; i < size; i++) {
        for (short j = 0; j < size; j++) {
            for (short k = 0; k < size; k++) {
                if (field[i][j][k] == -1) {
                    AddOpenedCell(fieldData, 3, size, i, j, k); // Open the mine cell
                }
            }
        }
    }
}

void PinAllFlags(short ***field, short size, FieldData& fieldData) {
    for (short i = 0; i < size; i++) {
        for (short j = 0; j < size; j++) {
            for (short k = 0; k < size; k++) {
                if (field[i][j][k] == -1) {
                    AddFlaggedCell(fieldData, 3, size, i, j, k); // Flag the mine cell
                }
            }
        }
    }
}

int CountMinesAroundCell(short ***field, short size, short x, short y, short z) {
    int count = 0;
    for (short dx = -1; dx <= 1; dx++) {
        for (short dy = -1; dy <= 1; dy++) {
            for (short dz = -1; dz <= 1; dz++) {
                if (dx == 0 && dy == 0 && dz == 0) continue; // Skip the cell itself
                short nx = x + dx, ny = y + dy, nz = z + dz;
                if (nx >= 0 && nx < size && ny >= 0 && ny < size && nz >= 0 && nz < size &&
                    field[nx][ny][nz] == -1) { // If adjacent cell is a mine
                    count++; // Increment count
                }
            }
        }
    }
    return count;
}

int CountOpenedCellsAroundCell(FieldData& fieldData, short ***field, short size, short x, short y, short z) {
    int count = 0;
    for (short dx = -1; dx <= 1; dx++) {
        for (short dy = -1; dy <= 1; dy++) {
            for (short dz = -1; dz <= 1; dz++) {
                if (dx == 0 && dy == 0 && dz == 0) continue; // Skip the cell itself
                short nx = x + dx, ny = y + dy, nz = z + dz;
                if (nx >= 0 && nx < size && ny >= 0 && ny < size && nz >= 0 && nz < size &&
                    isOpened(fieldData, 3, nx, ny, nz)) { // If adjacent cell is opened
                    count++; // Increment count
                }
            }
        }
    }
    return count;
}

int CountFlagedCellsAroundCell(FieldData& fieldData, short ***field, short size, short x, short y, short z) {
    int count = 0;
    for (short dx = -1; dx <= 1; dx++) {
        for (short dy = -1; dy <= 1; dy++) {
            for (short dz = -1; dz <= 1; dz++) {
                if (dx == 0 && dy == 0 && dz == 0) continue; // Skip the cell itself
                short nx = x + dx, ny = y + dy, nz = z + dz;
                if (nx >= 0 && nx < size && ny >= 0 && ny < size && nz >= 0 && nz < size &&
                    isFlagged(fieldData, 3, nx, ny, nz)) { // If adjacent cell is flagged
                    count++; // Increment count
                }
            }
        }
    }
    return count;
}

bool OpenAllAroundCells_ExeptFlagedCells(FieldData& fieldData, short ***field, short size, short x, short y, short z) {
    bool gameOver = false; // Flag to check if game is over
    for (short dx = -1; dx <= 1; dx++) {
        for (short dy = -1; dy <= 1; dy++) {
            for (short dz = -1; dz <= 1; dz++) {
                if (dx == 0 && dy == 0 && dz == 0) continue; // Skip the cell itself
                short nx = x + dx, ny = y + dy, nz = z + dz;
                if (nx >= 0 && nx < size && ny >= 0 && ny < size && nz >= 0 && nz < size) {
                    if (!isFlagged(fieldData, 3, nx, ny, nz) && !isOpened(fieldData, 3, nx, ny, nz)) {
                        AddOpenedCell(fieldData, 3, size, nx, ny, nz);
                        if (field[nx][ny][nz] == -1) {
                            gameOver = true; // Game over if a mine is opened
                        }
                    }
                }
            }
        }
    }
    return gameOver;
}

void RecursiveOpenCells(FieldData& fieldData, short ***field, short size, short x, short y, short z) {
    if (isOpened(fieldData, 3, x, y, z)) return; // If cell is already opened
    AddOpenedCell(fieldData, 3, size, x, y, z); // Open the cell

    int minesCount = CountMinesAroundCell(field, size, x, y, z);
    if (minesCount == 0) { // If no mines around
        for (short dx = -1; dx <= 1; dx++) {
            for (short dy = -1; dy <= 1; dy++) {
                for (short dz = -1; dz <= 1; dz++) {
                    if (dx == 0 && dy == 0 && dz == 0) continue; // Skip the cell itself
                    short nx = x + dx, ny = y + dy, nz = z + dz;
                    if (nx >= 0 && nx < size && ny >= 0 && ny < size && nz >= 0 && nz < size) {
                        RecursiveOpenCells(fieldData, field, size, nx, ny, nz); // Recursively open adjacent cells
                    }
                }
            }
        }
    }
}

// ### 4D Minesweeper ###

void OpenAllMines(short ****field, short size, FieldData& fieldData, short dimensions) {
    for (short i = 0; i < size; i++) {
        for (short j = 0; j < size; j++) {
            for (short k = 0; k < size; k++) {
                for (short l = 0; l < size; l++) {
                    if (field[i][j][k][l] == -1) {
                        AddOpenedCell(fieldData, 4, size, i, j, k, l); // Open the mine cell
                    }
                }
            }
        }
    }
}

void PinAllFlags(short ****field, short size, FieldData& fieldData, short dimensions) {
    for (short i = 0; i < size; i++) {
        for (short j = 0; j < size; j++) {
            for (short k = 0; k < size; k++) {
                for (short l = 0; l < size; l++) {
                    if (field[i][j][k][l] == -1) {
                        AddFlaggedCell(fieldData, 4, size, i, j, k, l); // Flag the mine cell
                    }
                }
            }
        }
    }
}

int CountMinesAroundCell(short ****field, short size, short x, short y, short z, short w) {
    int count = 0;
    for (short dx = -1; dx <= 1; dx++) {
        for (short dy = -1; dy <= 1; dy++) {
            for (short dz = -1; dz <= 1; dz++) {
                for (short dw = -1; dw <= 1; dw++) {
                    if (dx == 0 && dy == 0 && dz == 0 && dw == 0) continue; // Skip the cell itself
                    short ni = x + dx, nj = y + dy, nk = z + dz, nl = w + dw;
                    if (ni >= 0 && ni < size && nj >= 0 && nj < size &&
                        nk >= 0 && nk < size && nl >= 0 && nl < size &&
                        field[ni][nj][nk][nl] == -1) {
                        count++; // Increment count for adjacent mines
                    }
                }
            }
        }
    }
    return count;
}

int CountOpenedCellsAroundCell(FieldData& fieldData, short ****field, short size, short x, short y, short z, short w) {
    int count = 0;
    for (short dx = -1; dx <= 1; dx++) {
        for (short dy = -1; dy <= 1; dy++) {
            for (short dz = -1; dz <= 1; dz++) {
                for (short dw = -1; dw <= 1; dw++) {
                    if (dx == 0 && dy == 0 && dz == 0 && dw == 0) continue; // Skip the cell itself
                    short ni = x + dx, nj = y + dy, nk = z + dz, nl = w + dw;
                    if (ni >= 0 && ni < size && nj >= 0 && nj < size &&
                        nk >= 0 && nk < size && nl >= 0 && nl < size &&
                        isOpened(fieldData, 4, ni, nj, nk, nl)) {
                        count++; // Increment count for opened adjacent cells
                    }
                }
            }
        }
    }
    return count;
}

int CountFlagedCellsAroundCell(FieldData& fieldData, short ****field, short size, short x, short y, short z, short w) {
    int count = 0;
    for (short dx = -1; dx <= 1; dx++) {
        for (short dy = -1; dy <= 1; dy++) {
            for (short dz = -1; dz <= 1; dz++) {
                for (short dw = -1; dw <= 1; dw++) {
                    if (dx == 0 && dy == 0 && dz == 0 && dw == 0) continue; // Skip the cell itself
                    short ni = x + dx, nj = y + dy, nk = z + dz, nl = w + dw;
                    if (ni >= 0 && ni < size && nj >= 0 && nj < size &&
                        nk >= 0 && nk < size && nl >= 0 && nl < size &&
                        isFlagged(fieldData, 4, ni, nj, nk, nl)) {
                        count++; // Increment count for opened adjacent cells
                    }
                }
            }
        }
    }
    return count;
}

bool OpenAllAroundCells_ExeptFlagedCells(FieldData& fieldData, short ****field, short size, short x, short y, short z, short w) {
    bool gameOver = false;
    for (short dx = -1; dx <= 1; dx++) {
        for (short dy = -1; dy <= 1; dy++) {
            for (short dz = -1; dz <= 1; dz++) {
                for (short dw = -1; dw <= 1; dw++) {
                    if (dx == 0 && dy == 0 && dz == 0 && dw == 0) continue; // Skip the cell itself
                    short nx = x + dx, ny = y + dy, nz = z + dz, nw = w + dw;
                    if (nx >= 0 && nx < size && ny >= 0 && ny < size &&
                        nz >= 0 && nz < size && nw >= 0 && nw < size) {
                        if (!isFlagged(fieldData, 4, nx, ny, nz, nw) && !isOpened(fieldData, 4, nx, ny, nz, nw)) {
                            AddOpenedCell(fieldData, 4, size, nx, ny, nz, nw);
                            if (field[nx][ny][nz][nw] == -1) {
                                gameOver = true; // Game over if a mine is opened
                            }
                        }
                    }
                }
            }
        }
    }
    return gameOver; // Return true if a mine was opened
}

void RecursiveOpenCells(FieldData& fieldData, short ****field, short size, short x, short y, short z, short w) {
    if (field[w][z][y][x] == -1) return; // If cell is a mine, do not open
    if (field[w][z][y][x] > 0) return; // If cell has adjacent mines, do not open
    if (isOpened(fieldData, 4, x, y, z, w)) return; // If cell is already opened
    AddOpenedCell(fieldData, 4, size, x, y, z, w); // Open the cell

    int minesCount = CountMinesAroundCell(field, size, x, y, z, w);
    if (minesCount == 0) { // If no mines around
        for (short dx = -1; dx <= 1; dx++) {
            for (short dy = -1; dy <= 1; dy++) {
                for (short dz = -1; dz <= 1; dz++) {
                    for (short dw = -1; dw <= 1; dw++) {
                        if (dx == 0 && dy == 0 && dz == 0 && dw == 0) continue; // Skip the cell itself
                        if ((dx == -1 || dx == 1) && (dy == -1 || dy == 1) && (dz == -1 || dz == 1) && (dw == -1 || dw == 1)) continue; // Skip diagonals
                        short nx = x + dx, ny = y + dy, nz = z + dz, nw = w + dw;
                        if (nx >= 0 && nx < size && ny >= 0 && ny < size &&
                            nz >= 0 && nz < size && nw >= 0 && nw < size) {
                            RecursiveOpenCells(fieldData, field, size, nx, ny, nz, nw); // Recursively open adjacent cells
                        }
                    }
                }
            }
        }
    }
}

// ### --- ###

void GiveTotalPrizesToUser(int UserId, int dimensions, int loses_count, int size, int countOfMines) {
    ArrayUsers au;
    Load_Users_Data(au);
    
    // Basic multipliers
    double base_xp = 50;
    double base_coins = 20;

    // Difficulty calculation
    double difficulty_multiplier = dimensions * 0.8 + (countOfMines / double(size*size)) * 5.0;

    // Calculation of penalty for losses
    double lose_penalty = 1.0 / (1 + loses_count * 0.5);

    // Final count
    int total_xp = int(base_xp * size * difficulty_multiplier * lose_penalty);
    int total_coins = int(base_coins * difficulty_multiplier * lose_penalty + Randint(0, 10));

    system("cls");
    // cout << "Total xp: " << total_xp << endl;
    // cout << "Total coins: " << total_coins << endl;

    int pos = Get_position_of_user(au, UserId);

    int multiplier = 1;
    if (loses_count == 0) {
        multiplier = 2;
            if (dimensions == 1) {
            au.ptrUs[pos]->games_played_1D++;
        } else if (dimensions == 2) {
            au.ptrUs[pos]->games_played_2D++;
        } else if (dimensions == 3) {
            au.ptrUs[pos]->games_played_3D++;
        } else if (dimensions == 4) {
            au.ptrUs[pos]->games_played_4D++;
        } else {
            cout << "error" << endl;
            cout << "cant write data" << endl;
            system("pause");
            return;
        }
    }

    if (dimensions == 2) {
        au.ptrUs[pos]->experience += total_xp*multiplier;
        au.ptrUs[pos]->minecoins += total_coins*multiplier;
    } else if (dimensions == 3) {
        au.ptrUs[pos]->experience += total_xp*multiplier;
        au.ptrUs[pos]->minecoins += total_coins*multiplier;
    } else if (dimensions == 4) {
        au.ptrUs[pos]->experience += total_xp*multiplier;
        au.ptrUs[pos]->minecoins += total_coins*multiplier;
    } else {
        cout << "error" << endl;
        cout << "cant write data" << endl;
        system("pause");
        return;
    }
    
    cout << "Congratulations dear " << au.ptrUs[pos]->username << "! There is your awards:" << endl;
    cout << "Experience: +" << total_xp*multiplier << endl;
    cout << "Minecoins: +" << total_coins*multiplier << endl;
    system("pause");
    Fill_File_With_Users_Data(au);
}

void PrintKayboard(const KaysData kaysData, int dimensions) {
    cout << "KayBoard REFERENCE (actual kays)" << endl << endl;
    cout << "   " << (kaysData.press_1 == true ? "# " : "1 ") << (kaysData.press_2 == true ? "#" : "2") << 
            "        " << (kaysData.press_0 == true ? "#" : "0") << endl;
    cout << "    " << (kaysData.press_q == true ? "# " : "q ") << 
            (dimensions != 4 ? "  " : (kaysData.press_w == true ? "# " : "w ")) << 
            (kaysData.press_e == true ? "# " : "e ") << (kaysData.press_r == true ? "# " : "r ") << endl;
    cout << "    " << (dimensions < 3 ? "  " : (kaysData.press_a == true ? "# " : "a ")) << 
            (dimensions != 4 ? "  " : (kaysData.press_s == true ? "# " : "s ")) << 
            (dimensions < 3 ? "  " : (kaysData.press_d == true ? "# " : "d ")) << "          " << 
            (dimensions < 2 ? "  " : (kaysData.press_up == true ? "# " : "^ ")) << endl;
    cout << "                  " << (kaysData.press_left == true ? "# " : "< ") << 
            (dimensions < 2 ? "  " : (kaysData.press_down == true ? "# " : "- ")) << 
            (kaysData.press_right == true ? "#" : ">") << endl << endl;
}

void FreeFieldData(FieldData& fieldData) {
    if (fieldData.selected2D != nullptr) {
        delete[] fieldData.selected2D;
    }
    if (fieldData.selected3D != nullptr) {
        delete[] fieldData.selected3D;
    }
    if (fieldData.selected4D != nullptr) {
        delete[] fieldData.selected4D;
    }
    if (fieldData.opened != nullptr) {
        for (int i = 0; i < fieldData.opened_count; i++) {
            delete[] fieldData.opened[i];
        }
        delete[] fieldData.opened;
    }
    if (fieldData.flagged != nullptr) {
        for (int i = 0; i < fieldData.flagged_count; i++) {
            delete[] fieldData.flagged[i];
        }
        delete[] fieldData.flagged;
    }
}
