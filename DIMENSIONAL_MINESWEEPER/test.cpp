#include "common_code.cpp"
using namespace std;

struct FieldData {
    // Currently selected cell
    int selected1D = 0;//  -  -  -  -  -  -  -  - // 1D: just index
    int* selected2D = new int[2]{0, 0};// -  -  - // 2D: x, y
    int* selected3D = new int[3]{0, 0, 0};// -  - // 3D: x, y, z
    int* selected4D = new int[4]{0, 0, 0, 0};// - // 4D: x, y, z, w

    // Previous selected cell
    int pastSelected1D = 0;// -  -  -  -  -  -  - // 1D: just index
    int* pastSelected2D = new int[2]{0, 0};//-  - // 2D: x, y
    int* pastSelected3D = new int[3]{0, 0, 0};//- // 3D: x, y, z
    int* pastSelected4D = new int[4]{0, 0, 0, 0}; // 4D: x, y, z, w

    // Vector of difference current and previous selected cells
    int vector = selected1D - pastSelected1D;// -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  // 1D: just index
    int* vector2D = new int[2]{selected2D[0] - pastSelected2D[0], selected2D[1] - pastSelected2D[1]};//  -  -  -  // 2D: x, y
    int* vector3D = new int[3]{selected3D[0] - pastSelected3D[0], selected3D[1] - pastSelected3D[1], 
                    selected3D[2] - pastSelected3D[2]};//-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  // 3D: x, y, z
    int* vector4D = new int[4]{selected4D[0] - pastSelected4D[0], selected4D[1] - pastSelected4D[1], 
                    selected4D[2] - pastSelected4D[2], selected4D[3] - pastSelected4D[3]};// -  -  -  -  -  -  -  // 4D: x, y, z, w

    // Opened cells
    int** opened4D = nullptr;

    // Flagged cells
    int** flagged4D = nullptr;

    // Counts of opened and flagged cells
    int opened_count = 0;
    int flagged_count = 0;
    int opened_size = 0;
    int flagged_size = 0;
};

void PrintField(short ****field, short size)
{
    for (short i = 0; i < size; i++) {
        for (short j = 0; j < size; j++) {
            // Output the current "i,j" slice
            for (short k = 0; k < size; k++) {
                for (short l = 0; l < size; l++) {
                    if (field[i][j][k][l] == -1) {
                        cout << setw(3) << "M";
                    } else {
                        cout << setw(3) << field[i][j][k][l];
                    }
                }
                cout << "   "; // Space between "k" slices
            }
            cout << endl;
        }
        for (short k = 0; k < size; k++) {
            // Output a separator line for each "k" slice
            cout << "------------------------";
        }
        cout << endl;
    }
}

double degree(double x, int y) {
    double result = 1;
    if (y < 0) {
        x = 1 / x;
        y = -y;
    }

    for (int i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}

int degree(int x, int y) {
    int result = 1;
    if (y < 0) {
        x = 1 / x;
        y = -y;
    }

    for (int i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}

double Randint(int min, int max, int frction_step = 1) {
    if (min > max) {
        double temp = min;
        min = max;
        max = temp;
    }
    return (min*frction_step + rand() % int(max*frction_step - min*frction_step + 1)) / frction_step; // Generate a random integer between min and max in 1/step
}

void GiveTotalPrizesToUser(int dimensions, int loses_count, int size, int countOfMines) {
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

    cout << "Total xp: " << total_xp << endl;
    cout << "Total coins: " << total_coins << endl;
}

void GetTopLeftCornerCords(FieldData fieldData, int *pastCords, int frame_size, int dimensions = 2, int border = 1) {
    int newCords[2] = {0, 0}; // Initialize new coordinates
    int freeZone_size = frame_size - 2 * border; // Calculate the size of the free zone
    if (dimensions == 1) {
        int freeZone[2] = {
            pastCords[0] + border, // Left x
            pastCords[0] + frame_size - border // Right x
        };
        if (fieldData.selected1D < freeZone[0]) {
            newCords[0] = fieldData.selected1D - border; // Move left
        } else if (fieldData.selected1D > freeZone[1]) {
            newCords[0] = fieldData.selected1D - freeZone_size; // Move right
        } else {
            newCords[0] = pastCords[0]; // Reset to past coordinates
        }
    } else {
        int freeZone[4] = {
            pastCords[0] + border, // Top left x
            pastCords[1] + border, // Top left y
            pastCords[0] + frame_size - border, // Bottom right x
            pastCords[1] + frame_size - border // Bottom right y
        };
        if (fieldData.selected2D != nullptr) {
            // Check if the selected cell is within the free zone
            if (fieldData.selected2D[0] <= freeZone[0]) {
                newCords[0] = fieldData.selected2D[0] - border; // Move left
            } else if (fieldData.selected2D[0] >= freeZone[2]) {
                newCords[0] = fieldData.selected2D[0] - freeZone_size; // Move right
            } if (fieldData.selected2D[1] <= freeZone[1]) {
                newCords[1] = fieldData.selected2D[1] - border; // Move up
            } else if (fieldData.selected2D[1] >= freeZone[3]) {
                newCords[1] = fieldData.selected2D[1] - freeZone_size; // Move down
            } else {
                newCords[0] = pastCords[0]; // Reset to past coordinates
                newCords[1] = pastCords[1];
            }
        } else {
            newCords[0] = pastCords[0]; // Reset to past coordinates
            newCords[1] = pastCords[1];
        }
    }
    pastCords[0] = newCords[0]; // Update past coordinates
    if (dimensions > 1) {
        pastCords[1] = newCords[1]; // Update past coordinates
    }
}

void GetTopLeftCornerCords(FieldData fieldData, int *pastCords, int frame_size, int dimensions = 2, int border = 1) {
    int newCords[2] = {0, 0}; // Initialize new coordinates
    int freeZone_size = frame_size - 2 * border; // Calculate the size of the free zone
    if (dimensions == 1) {
        int freeZone[2] = {
            pastCords[0] + border, // Left x
            pastCords[0] + frame_size - border // Right x
        };
        if (fieldData.selected1D < freeZone[0]) {
            newCords[0] = fieldData.selected1D - border; // Move left
        } else if (fieldData.selected1D > freeZone[1]) {
            newCords[0] = fieldData.selected1D - freeZone_size; // Move right
        } else {
            newCords[0] = pastCords[0]; // Stay
        }
    } else { // local processing of 2D coordinates from any dimension
        int sel2D[2] = {0, 0};
        if (dimensions == 2 && fieldData.selected2D != nullptr) {
            sel2D[0] = fieldData.selected2D[0];
            sel2D[1] = fieldData.selected2D[1];
        } else if (dimensions == 3 && fieldData.selected3D != nullptr) {
            sel2D[0] = fieldData.selected3D[0];
            sel2D[1] = fieldData.selected3D[1];
        } else if (dimensions == 4 && fieldData.selected4D != nullptr) {
            sel2D[0] = fieldData.selected4D[0];
            sel2D[1] = fieldData.selected4D[1];
        }
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

int main()
{
    srand(time(NULL));

    int dimensions = 3;
    int loses_count = 0;
    int size = 1000;
    
    // GiveTotalPrizesToUser(dimensions, loses_count, size, degree(size, dimensions) / 25);

    FieldData fieldData;
    int pastCords[2] = {3, 3};
    fieldData.selected2D[0] = 8;
    fieldData.selected2D[1] = 8;

    cout << "Selected cords: " << fieldData.selected2D[0] << ", " << fieldData.selected2D[1] << endl;
    cout << "Past cords: " << pastCords[0] << ", " << pastCords[1] << endl << endl;

    GetTopLeftCornerCords(fieldData, pastCords, 6, 2, 1);

    cout << "Past cords: " << pastCords[0] << ", " << pastCords[1] << endl;

    return 0;
}