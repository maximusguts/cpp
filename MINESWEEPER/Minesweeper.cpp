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

    void setColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
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
    }

    void update() {
        if(gameStarted && !gameEnded) {
            elapsedTime = (int)(time(NULL) - startTime);
        }
    }

    void draw() {
        clearScreen();
        
        setColor(15); // Білий для заголовка
        cout << "=== MINESWEEPER ===" << endl;
        cout << "Time: " << elapsedTime << "s | Flags left: " << (mineCount - flagCount) << endl;
        cout << "Coins: " << playerStats->coins << endl;
        cout << endl;
        
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                // Малювання курсора
                if(x == cursorX && y == cursorY) {
                    setColor(15); cout << "[";
                } else {
                    cout << " ";
                }
                
                // Вміст клітинки
                if(gameEnded && mines[y][x]) {
                    setColor(12); // Світло-червоний для мін
                    cout << "*";
                } else if(states[y][x] == FLAGGED) {
                    setColor(14); // Жовтий для прапорців
                    cout << "F";
                } else if(states[y][x] == REVEALED) {
                    if(mines[y][x]) {
                        setColor(12); cout << "*";
                    } else if(board[y][x] == 0) {
                        cout << " ";
                    } else {
                        // Кольори для цифр
                        switch(board[y][x]) {
                            case 1: setColor(9);  break; // Світло-синій
                            case 2: setColor(10); break; // Світло-зелений
                            case 3: setColor(12); break; // Світло-червоний
                            case 4: setColor(1);  break; // Темно-синій
                            case 5: setColor(4);  break; // Темно-червоний
                            case 6: setColor(11); break; // Бірюзовий
                            case 7: setColor(8);  break; // Сірий
                            case 8: setColor(7);  break; // Білий
                        }
                        cout << board[y][x];
                    }
                } else {
                    setColor(7); // Звичайний сірий для закритих
                    cout << "#";
                }
                
                // Закриття курсора
                if(x == cursorX && y == cursorY) {
                    setColor(15); cout << "]";
                } else {
                    cout << " ";
                }
            }
            setColor(7); // Скидання кольору в кінці рядка
            cout << endl;
        }
        
        setColor(15);
        cout << endl << "Controls: Arrows (move), 1 (Reveal/Chord), 2 (Flag)" << endl;
        cout << "R (Restart), Q (Quit)" << endl;
        
        if(gameEnded) {
            if(gameWon) {
                setColor(10); cout << endl << "CONGRATULATIONS! YOU WON!" << endl;
            } else {
                setColor(12); cout << endl << "GAME OVER! You hit a mine!" << endl;
            }
            setColor(15);
            cout << "Press N for next game or Q to quit" << endl;
        }
    }

    bool handleInput() {
        if(!_kbhit()) return true;
        
        int key = _getch();
        if(key == 224) { 
            key = _getch();
            switch(key) {
                case 72: cursorY = max(0, cursorY - 1); break;
                case 80: cursorY = min(height - 1, cursorY + 1); break;
                case 75: cursorX = max(0, cursorX - 1); break;
                case 77: cursorX = min(width - 1, cursorX + 1); break;
            }
        } else {
            switch(key) {
                case '1': // Reveal or Chord
                    if(!gameEnded) {
                        if (states[cursorY][cursorX] == HIDDEN) {
                            revealCell(cursorX, cursorY);
                        } else if (states[cursorY][cursorX] == REVEALED) {
                            performChord(cursorX, cursorY);
                        }
                    }
                    break;
                case '2': // Flag
                    if(!gameEnded) toggleFlag(cursorX, cursorY);
                    break;
                case 'r': case 'R': restart(); break;
                case 'n': case 'N': if(gameEnded) return false; break;
                case 'q': case 'Q': case 27: return false;
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
