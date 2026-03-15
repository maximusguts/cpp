#include <iostream>
#include <conio.h>     // _kbhit(), _getch()
#include <windows.h>   // Sleep(), system("cls")
 
 
using namespace std;
 
const int width = 20;
const int height = 20;
 
// Напрямки руху змійки
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;
 
int x, y;               // позиція голови
int fruitX, fruitY;     // позиція фрукта
int tailX[100], tailY[100]; // масив для тіла
int nTail;              // довжина тіла
int score;              // очки
bool gameOver;          // кінець гри
 
// Початкове налаштування
void Setup() {
    srand((unsigned)time(NULL));
    gameOver = false;
    dir = STOP;
    x = width / 2;s
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
}
 
// Малювання поля
void Draw() {
    system("cls");
 
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;
 
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#";
 
            if (i == y && j == x)
                cout << "O"; // голова
            else if (i == fruitY && j == fruitX)
                cout << "F"; // фрукт
            else {
                bool printed = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // тіло
                        printed = true;
                        break;
                    }
                }
                if (!printed) cout << " ";
            }
 
            if (j == width - 1) cout << "#";
        }
        cout << endl;
    }
 
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;
 
    cout << "Score: " << score << endl;
    cout << "Use W A S D to move. Press X to quit." << endl;
}
 
// Обробка вводу
void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a': case 'A': dir = LEFT; break;
        case 'd': case 'D': dir = RIGHT; break;
        case 'w': case 'W': dir = UP; break;
        case 's': case 'S': dir = DOWN; break;
        case 'x': case 'X': gameOver = true; break;
        }
    }
}
 
// Логіка руху
void Logic() {
    // рух хвоста
    int prevX = tailX[0], prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
 
    // рух голови
    switch (dir) {
    case LEFT:  x--; break;
    case RIGHT: x++; break;
    case UP:    y--; break;
    case DOWN:  y++; break;
    }
 
    // перевірка на зіткнення зі стіною
    if (x < 0 || x >= width || y < 0 || y >= height)
        gameOver = true;
 
    // перевірка на зіткнення з собою
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
 
    // з'їли фрукт
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}
 
// Основна програма
int main() {
 
    Setup();
 
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100); // швидкість гри
    }
 
    cout << "\nGame Over! Final Score: " << score << endl;
    return 0;
}