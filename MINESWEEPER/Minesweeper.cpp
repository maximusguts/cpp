#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <conio.h>
#include <windows.h>

using namespace std;

const int MAX_SIZE = 30;
const int MAX_GAMES = 1000;
const int MAX_NAME_LENGTH = 50;

// Game difficulty levels
enum Difficulty {
    BEGINNER = 0,
    INTERMEDIATE = 1,
    EXPERT = 2,
    CUSTOM = 3
};

// Cell states
enum CellState {
    HIDDEN = 0,
    REVEALED = 1,
    FLAGGED = 2
};

// Game result structure
struct GameResult {
    char date[20];
    int difficulty;
    int time;
    bool won;
    int width, height, mines;
};

// Player statistics
struct PlayerStats {
    int coins;
    int experience;
    int level;
    int totalGames;
    int beginnerWins;
    int intermediateWins;
    int expertWins;
};

class MinesweeperSolver {
private:
    int** board;
    bool** mines;
    CellState** states;
    int width, height, mineCount;

public:
    MinesweeperSolver(int** gameBoard, bool** gameMines, CellState** gameStates, 
                     int w, int h, int mCount) {
        board = gameBoard;
        mines = gameMines;
        states = gameStates;
        width = w;
        height = h;
        mineCount = mCount;
    }

    bool getHint(int& hintX, int& hintY) {
        // Simple solver logic - find safe cells
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                if(states[y][x] == REVEALED && board[y][x] > 0) {
                    int flaggedCount = 0;
                    int hiddenCount = 0;
                    
                    // Count flagged and hidden neighbors
                    for(int dy = -1; dy <= 1; dy++) {
                        for(int dx = -1; dx <= 1; dx++) {
                            int nx = x + dx;
                            int ny = y + dy;
                            
                            if(nx >= 0 && nx < width && ny >= 0 && ny < height) {
                                if(states[ny][nx] == FLAGGED) flaggedCount++;
                                if(states[ny][nx] == HIDDEN) hiddenCount++;
                            }
                        }
                    }
                    
                    // If all mines are flagged, reveal safe cells
                    if(flaggedCount == board[y][x] && hiddenCount > 0) {
                        for(int dy = -1; dy <= 1; dy++) {
                            for(int dx = -1; dx <= 1; dx++) {
                                int nx = x + dx;
                                int ny = y + dy;
                                
                                if(nx >= 0 && nx < width && ny >= 0 && ny < height && 
                                   states[ny][nx] == HIDDEN) {
                                    hintX = nx;
                                    hintY = ny;
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
        return false;
    }
};

class Game {
private:
    int** board;
    bool** mines;
    CellState** states;
    int width, height, mineCount;
    int cursorX, cursorY;
    int flagCount;
    int revealedCount;
    bool gameStarted;
    bool gameEnded;
    bool gameWon;
    time_t startTime;
    int elapsedTime;
    PlayerStats* playerStats;
    MinesweeperSolver* solver;

    void initializeBoard() {
        // Allocate memory for arrays
        board = new int*[height];
        mines = new bool*[height];
        states = new CellState*[height];
        
        for(int i = 0; i < height; i++) {
            board[i] = new int[width];
            mines[i] = new bool[width];
            states[i] = new CellState[width];
        }
        
        // Initialize arrays
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                board[y][x] = 0;
                mines[y][x] = false;
                states[y][x] = HIDDEN;
            }
        }
    }

    void placeMines() {
        srand(time(NULL));
        int placedMines = 0;
        
        while(placedMines < mineCount) {
            int x = rand() % width;
            int y = rand() % height;
            
            // Don't place mine on cursor position or if already has mine
            if((x != cursorX || y != cursorY) && !mines[y][x]) {
                mines[y][x] = true;
                placedMines++;
            }
        }
        
        // Calculate numbers
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                if(!mines[y][x]) {
                    int count = 0;
                    for(int dy = -1; dy <= 1; dy++) {
                        for(int dx = -1; dx <= 1; dx++) {
                            int nx = x + dx;
                            int ny = y + dy;
                            if(nx >= 0 && nx < width && ny >= 0 && ny < height && mines[ny][nx]) {
                                count++;
                            }
                        }
                    }
                    board[y][x] = count;
                }
            }
        }
    }

    void revealCell(int x, int y) {
        if(x < 0 || x >= width || y < 0 || y >= height || states[y][x] != HIDDEN) {
            return;
        }
        
        if(!gameStarted) {
            gameStarted = true;
            startTime = time(NULL);
            placeMines();
            solver = new MinesweeperSolver(board, mines, states, width, height, mineCount);
        }
        
        states[y][x] = REVEALED;
        revealedCount++;
        
        if(mines[y][x]) {
            gameEnded = true;
            gameWon = false;
            return;
        }
        
        // Recursive reveal for empty cells
        if(board[y][x] == 0) {
            for(int dy = -1; dy <= 1; dy++) {
                for(int dx = -1; dx <= 1; dx++) {
                    revealCell(x + dx, y + dy);
                }
            }
        }
        
        // Check win condition
        if(revealedCount == width * height - mineCount) {
            gameEnded = true;
            gameWon = true;
        }
    }

    void toggleFlag(int x, int y) {
        if(x < 0 || x >= width || y < 0 || y >= height || states[y][x] == REVEALED) {
            return;
        }
        
        if(states[y][x] == HIDDEN) {
            states[y][x] = FLAGGED;
            flagCount++;
        } else if(states[y][x] == FLAGGED) {
            states[y][x] = HIDDEN;
            flagCount--;
        }
    }

    void performChord(int x, int y) {
        if(x < 0 || x >= width || y < 0 || y >= height || states[y][x] != REVEALED) {
            return;
        }
        
        int flaggedCount = 0;
        for(int dy = -1; dy <= 1; dy++) {
            for(int dx = -1; dx <= 1; dx++) {
                int nx = x + dx;
                int ny = y + dy;
                if(nx >= 0 && nx < width && ny >= 0 && ny < height && states[ny][nx] == FLAGGED) {
                    flaggedCount++;
                }
            }
        }
        
        if(flaggedCount == board[y][x]) {
            for(int dy = -1; dy <= 1; dy++) {
                for(int dx = -1; dx <= 1; dx++) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if(nx >= 0 && nx < width && ny >= 0 && ny < height && states[ny][nx] == HIDDEN) {
                        revealCell(nx, ny);
                    }
                }
            }
        }
    }

    void clearScreen() {
        system("cls");
    }

    void gotoxy(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

public:
    Game(int w, int h, int mines, PlayerStats* stats) {
        width = w;
        height = h;
        mineCount = mines;
        cursorX = w / 2;
        cursorY = h / 2;
        flagCount = 0;
        revealedCount = 0;
        gameStarted = false;
        gameEnded = false;
        gameWon = false;
        elapsedTime = 0;
        playerStats = stats;
        solver = nullptr;
        
        initializeBoard();
    }

    ~Game() {
        for(int i = 0; i < height; i++) {
            delete[] board[i];
            delete[] mines[i];
            delete[] states[i];
        }
        delete[] board;
        delete[] mines;
        delete[] states;
        
        if(solver) delete solver;
    }

    void restart() {
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                board[y][x] = 0;
                mines[y][x] = false;
                states[y][x] = HIDDEN;
            }
        }
        
        flagCount = 0;
        revealedCount = 0;
        gameStarted = false;
        gameEnded = false;
        gameWon = false;
        elapsedTime = 0;
        
        if(solver) {
            delete solver;
            solver = nullptr;
        }
    }

    void update() {
        if(gameStarted && !gameEnded) {
            elapsedTime = (int)(time(NULL) - startTime);
        }
    }

    void draw() {
        clearScreen();
        
        cout << "=== MINESWEEPER ===" << endl;
        cout << "Time: " << elapsedTime << "s | Flags left: " << (mineCount - flagCount) << endl;
        cout << "Coins: " << playerStats->coins << " | Use 'H' for hint (costs 10 coins)" << endl;
        cout << endl;
        
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                if(x == cursorX && y == cursorY) {
                    cout << "[";
                } else {
                    cout << " ";
                }
                
                if(gameEnded && mines[y][x]) {
                    cout << "*";
                } else if(states[y][x] == FLAGGED) {
                    cout << "F";
                } else if(states[y][x] == REVEALED) {
                    if(board[y][x] == 0) {
                        cout << " ";
                    } else {
                        cout << board[y][x];
                    }
                } else {
                    cout << "#";
                }
                
                if(x == cursorX && y == cursorY) {
                    cout << "]";
                } else {
                    cout << " ";
                }
            }
            cout << endl;
        }
        
        cout << endl;
        cout << "Controls: Arrow keys (move), 1 (reveal), 2 (flag), 3 (chord)" << endl;
        cout << "R (restart), H (hint), Q (quit)" << endl;
        
        if(gameEnded) {
            if(gameWon) {
                cout << endl << "CONGRATULATIONS! YOU WON!" << endl;
                cout << "Time: " << elapsedTime << " seconds" << endl;
                cout << "Press N for next game or Q to quit" << endl;
            } else {
                cout << endl << "GAME OVER! You hit a mine!" << endl;
                cout << "Press N for next game or Q to quit" << endl;
            }
        }
    }

    bool handleInput() {
        if(!_kbhit()) return true;
        
        int key = _getch();
        
        if(key == 224) { // Arrow keys
            key = _getch();
            switch(key) {
                case 72: // Up
                    cursorY = max(0, cursorY - 1);
                    break;
                case 80: // Down
                    cursorY = min(height - 1, cursorY + 1);
                    break;
                case 75: // Left
                    cursorX = max(0, cursorX - 1);
                    break;
                case 77: // Right
                    cursorX = min(width - 1, cursorX + 1);
                    break;
            }
        } else {
            switch(key) {
                case '1': // Reveal
                    if(!gameEnded) {
                        revealCell(cursorX, cursorY);
                    }
                    break;
                case '2': // Flag
                    if(!gameEnded) {
                        toggleFlag(cursorX, cursorY);
                    }
                    break;
                case '3': // Chord
                    if(!gameEnded) {
                        performChord(cursorX, cursorY);
                    }
                    break;
                case 'r':
                case 'R': // Restart
                    restart();
                    break;
                case 'h':
                case 'H': // Hint
                    if(!gameEnded && gameStarted && playerStats->coins >= 10 && solver) {
                        int hintX, hintY;
                        if(solver->getHint(hintX, hintY)) {
                            playerStats->coins -= 10;
                            cursorX = hintX;
                            cursorY = hintY;
                        }
                    }
                    break;
                case 'n':
                case 'N': // Next game
                    if(gameEnded) {
                        return false; // Signal to start new game
                    }
                    break;
                case 'q':
                case 'Q': // Quit
                    return false;
                case 27: // ESC
                    return false;
            }
        }
        return true;
    }

    bool isGameEnded() { return gameEnded; }
    bool isGameWon() { return gameWon; }
    int getElapsedTime() { return elapsedTime; }
    
    void finishGame() {
        if(gameWon) {
            int reward = 0;
            int exp = 0;
            
            // Calculate rewards based on difficulty and time
            if(width == 9 && height == 9) { // Beginner
                reward = 50;
                exp = 10;
                playerStats->beginnerWins++;
            } else if(width == 16 && height == 16) { // Intermediate
                reward = 100;
                exp = 25;
                playerStats->intermediateWins++;
            } else if(width == 30 && height == 16) { // Expert
                reward = 200;
                exp = 50;
                playerStats->expertWins++;
            }
            
            // Time bonus
            if(elapsedTime < 60) reward += 50;
            else if(elapsedTime < 120) reward += 25;
            
            playerStats->coins += reward;
            playerStats->experience += exp;
            playerStats->totalGames++;
            
            // Level up calculation
            playerStats->level = 1 + (playerStats->experience / 100);
        }
    }
};

class GameManager {
private:
    PlayerStats playerStats;
    GameResult gameHistory[MAX_GAMES];
    int gameCount;

    void loadPlayerData() {
        ifstream file("player_data.dat", ios::binary);
        if(file.is_open()) {
            file.read(reinterpret_cast<char*>(&playerStats), sizeof(PlayerStats));
            file.read(reinterpret_cast<char*>(&gameCount), sizeof(int));
            file.read(reinterpret_cast<char*>(gameHistory), sizeof(GameResult) * min(gameCount, MAX_GAMES));
            file.close();
        } else {
            // Initialize new player
            playerStats.coins = 100;
            playerStats.experience = 0;
            playerStats.level = 1;
            playerStats.totalGames = 0;
            playerStats.beginnerWins = 0;
            playerStats.intermediateWins = 0;
            playerStats.expertWins = 0;
            gameCount = 0;
        }
    }

    void savePlayerData() {
        ofstream file("player_data.dat", ios::binary);
        if(file.is_open()) {
            file.write(reinterpret_cast<const char*>(&playerStats), sizeof(PlayerStats));
            file.write(reinterpret_cast<const char*>(&gameCount), sizeof(int));
            file.write(reinterpret_cast<const char*>(gameHistory), sizeof(GameResult) * gameCount);
            file.close();
        }
    }

    void saveGameResult(int difficulty, int gameDuration, bool won, int width, int height, int mines) {
        if(gameCount < MAX_GAMES) {
            GameResult& result = gameHistory[gameCount];
            
            time_t now = time(0);
            struct tm* timeinfo = localtime(&now);
            strftime(result.date, 20, "%Y-%m-%d %H:%M", timeinfo);
            
            result.difficulty = difficulty;
            result.time = gameDuration;
            result.won = won;
            result.width = width;
            result.height = height;
            result.mines = mines;
            
            gameCount++;
        }
    }

    void showMainMenu() {
        system("cls");
        cout << "================================" << endl;
        cout << "       MINESWEEPER GAME        " << endl;
        cout << "================================" << endl;
        cout << endl;
        cout << "Welcome to the classic Minesweeper!" << endl;
        cout << "Clear all cells without hitting mines!" << endl;
        cout << endl;
        cout << "1. Start New Game" << endl;
        cout << "2. View Game History" << endl;
        cout << "3. View Player Statistics" << endl;
        cout << "4. Exit Game" << endl;
        cout << endl;
        cout << "Choose an option (1-4): ";
    }

    int getDifficultyChoice() {
        system("cls");
        cout << "Choose Difficulty:" << endl;
        cout << "1. Beginner (9x9, 10 mines)" << endl;
        cout << "2. Intermediate (16x16, 40 mines)" << endl;
        cout << "3. Expert (30x16, 99 mines)" << endl;
        cout << "4. Custom" << endl;
        cout << "5. Back to Main Menu" << endl;
        cout << endl;
        cout << "Choose option (1-5): ";
        
        int choice;
        cin >> choice;
        return choice;
    }

    void showGameHistory() {
        system("cls");
        cout << "=== GAME HISTORY ===" << endl;
        cout << endl;
        
        if(gameCount == 0) {
            cout << "No games played yet!" << endl;
        } else {
            cout << "Date/Time\t\tDifficulty\tTime\tResult\tSize" << endl;
            cout << "------------------------------------------------------------" << endl;
            
            for(int i = gameCount - 1; i >= max(0, gameCount - 20); i--) {
                cout << gameHistory[i].date << "\t";
                
                switch(gameHistory[i].difficulty) {
                    case BEGINNER: cout << "Beginner\t"; break;
                    case INTERMEDIATE: cout << "Intermediate\t"; break;
                    case EXPERT: cout << "Expert\t\t"; break;
                    case CUSTOM: cout << "Custom\t\t"; break;
                }
                
                cout << gameHistory[i].time << "s\t";
                cout << (gameHistory[i].won ? "WIN" : "LOSE") << "\t";
                cout << gameHistory[i].width << "x" << gameHistory[i].height << endl;
            }
        }
        
        cout << endl << "Press any key to continue...";
        _getch();
    }

    void showPlayerStats() {
        system("cls");
        cout << "=== PLAYER STATISTICS ===" << endl;
        cout << endl;
        cout << "Coins: " << playerStats.coins << endl;
        cout << "Experience: " << playerStats.experience << endl;
        cout << "Level: " << playerStats.level << endl;
        cout << "Total Games Played: " << playerStats.totalGames << endl;
        cout << endl;
        cout << "Games Won:" << endl;
        cout << "  Beginner: " << playerStats.beginnerWins << endl;
        cout << "  Intermediate: " << playerStats.intermediateWins << endl;
        cout << "  Expert: " << playerStats.expertWins << endl;
        cout << endl;
        
        if(playerStats.totalGames > 0) {
            int totalWins = playerStats.beginnerWins + playerStats.intermediateWins + playerStats.expertWins;
            double winRate = (double)totalWins / playerStats.totalGames * 100;
            cout << "Overall Win Rate: " << winRate << "%" << endl;
        }
        
        cout << endl << "Press any key to continue...";
        _getch();
    }

    void playGame(int width, int height, int mines, int difficulty) {
        Game game(width, height, mines, &playerStats);
        
        while(true) {
            game.update();
            game.draw();
            
            if(!game.handleInput()) {
                if(game.isGameEnded()) {
                    game.finishGame();
                    saveGameResult(difficulty, game.getElapsedTime(), game.isGameWon(), width, height, mines);
                    savePlayerData();
                    
                    // Wait for user input to continue
                    cout << "Press any key to continue...";
                    _getch();
                }
                break;
            }
            
            if(game.isGameEnded()) {
                game.draw(); // Redraw to show final state
            }
            
            Sleep(50); // Small delay to prevent excessive CPU usage
        }
    }

public:
    GameManager() {
        gameCount = 0;
        loadPlayerData();
    }

    ~GameManager() {
        savePlayerData();
    }

    void run() {
        int choice;
        
        while(true) {
            showMainMenu();
            cin >> choice;
            
            switch(choice) {
                case 1: { // Start New Game
                    int difficulty = getDifficultyChoice();
                    
                    switch(difficulty) {
                        case 1: // Beginner
                            playGame(9, 9, 10, BEGINNER);
                            break;
                        case 2: // Intermediate
                            playGame(16, 16, 40, INTERMEDIATE);
                            break;
                        case 3: // Expert
                            playGame(30, 16, 99, EXPERT);
                            break;
                        case 4: { // Custom
                            int w, h, m;
                            cout << "Enter width (5-30): ";
                            cin >> w;
                            cout << "Enter height (5-30): ";
                            cin >> h;
                            cout << "Enter number of mines: ";
                            cin >> m;
                            
                            if(w >= 5 && w <= 30 && h >= 5 && h <= 30 && m > 0 && m < w * h) {
                                playGame(w, h, m, CUSTOM);
                            } else {
                                cout << "Invalid parameters!" << endl;
                                Sleep(2000);
                            }
                            break;
                        }
                        case 5: // Back
                            break;
                    }
                    break;
                }
                case 2: // View Game History
                    showGameHistory();
                    break;
                case 3: // View Player Statistics
                    showPlayerStats();
                    break;
                case 4: // Exit
                    cout << "Thanks for playing!" << endl;
                    return;
                default:
                    cout << "Invalid choice!" << endl;
                    Sleep(1000);
                    break;
            }
        }
    }
};

int main() {
    GameManager gameManager;
    gameManager.run();
    return 0;
}
