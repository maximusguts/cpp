#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

class Character {
public:
    string name;
    int strength, agility, vitality, magic;
    int level;
    bool changed;

    Character() : name(""), strength(1), agility(1), vitality(1), magic(1), level(1), changed(false) {}

    void print() const {
        cout << "===== CHARACTER INFO =====\n";
        cout << "Name: " << name << "\n";
        cout << "Level: " << level << "\n";
        cout << "Strength: " << strength << "\n";
        cout << "Agility: " << agility << "\n";
        cout << "Vitality: " << vitality << "\n";
        cout << "Magic: " << magic << "\n";
        cout << "===========================\n";
    }

    void levelUp() {
        string skill;
        cout << "Enter skill to level up (strength/agility/vitality/magic): ";
        cin >> skill;

        if (skill == "strength") strength++;
        else if (skill == "agility") agility++;
        else if (skill == "vitality") vitality++;
        else if (skill == "magic") magic++;
        else {
            cout << "Invalid skill!\n";
            return;
        }

        level++;
        changed = true;
        cout << "Skill upgraded! Level: " << level << endl;
    }

    friend ofstream& operator<<(ofstream& out, const Character& c) {
        out << c.name << " " << c.strength << " " << c.agility << " "
            << c.vitality << " " << c.magic << " " << c.level << endl;
        return out;
    }

    friend ifstream& operator>>(ifstream& in, Character& c) {
        in >> c.name >> c.strength >> c.agility >> c.vitality >> c.magic >> c.level;
        return in;
    }
};

bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

int main() {
    srand(time(0));
    Character hero;
    bool gameRunning = true;
    bool gameStarted = false;

    while (gameRunning) {
        cout << "\nNEW GAME\nLOAD GAME\nEXIT\n>";
        string command;
        cin >> command;

        if (command == "NEW" || command == "NEWGAME" || command == "NEW_GAME") {
            cout << "Enter name: ";
            cin >> hero.name;
            hero.strength = rand() % 5 + 1;
            hero.agility = rand() % 5 + 1;
            hero.vitality = rand() % 5 + 1;
            hero.magic = rand() % 5 + 1;
            hero.level = 1;
            hero.changed = true;
            gameStarted = true;
            cout << "Game started!\n";
        }

        else if (command == "LOAD" || command == "LOADGAME" || command == "LOAD_GAME") {
            if (hero.changed && gameStarted) {
                cout << "Current game will be lost. Continue? (y/n): ";
                char ans; cin >> ans;
                if (ans != 'y') continue;
            }

            string saveName;
            cout << "Enter save name: ";
            cin >> saveName;
            ifstream fin(saveName + ".sav");
            if (fin.is_open()) {
                fin >> hero;
                fin.close();
                gameStarted = true;
                hero.changed = false;
                cout << "Save loaded!\n";
            } else {
                cout << "Save not found!\n";
            }
        }

        else if (command == "EXIT") {
            cout << "Bye!\n";
            break;
        }

        // menu
        while (gameStarted) {
            cout << "\nNEW GAME\nLEVELUP\nPRINT\nSAVE GAME\nLOAD GAME\nEXIT\n>";
            string cmd;
            cin >> cmd;

            if (cmd == "LEVELUP") hero.levelUp();

            else if (cmd == "PRINT") hero.print();

            else if (cmd == "SAVE" || cmd == "SAVEGAME" || cmd == "SAVE_GAME") {
                string saveName;
                cout << "Enter save name: ";
                cin >> saveName;

                if (fileExists(saveName + ".sav")) {
                    cout << "Save already exists. Overwrite? (y/n): ";
                    char ans; cin >> ans;
                    if (ans != 'y') continue;
                }

                ofstream fout(saveName + ".sav");
                if (fout.is_open()) {
                    fout << hero;
                    fout.close();
                    hero.changed = false;
                    cout << "Game saved!\n";
                } else {
                    cout << "Error saving file!\n";
                }
            }

            else if (cmd == "LOAD" || cmd == "LOADGAME" || cmd == "LOAD_GAME") {
                if (hero.changed) {
                    cout << "Unsaved progress will be lost. Continue? (y/n): ";
                    char ans; cin >> ans;
                    if (ans != 'y') continue;
                }

                string saveName;
                cout << "Enter save name: ";
                cin >> saveName;

                ifstream fin(saveName + ".sav");
                if (fin.is_open()) {
                    fin >> hero;
                    fin.close();
                    hero.changed = false;
                    cout << "Save loaded!\n";
                } else {
                    cout << "Save not found!\n";
                }
            }

            else if (cmd == "NEW" || cmd == "NEWGAME" || cmd == "NEW_GAME") {
                cout << "Start new game? Unsaved progress will be lost. (y/n): ";
                char ans; cin >> ans;
                if (ans == 'y') {
                    gameStarted = false;
                    break;
                }
            }

            else if (cmd == "EXIT") {
                cout << "Exit to main menu? (y/n): ";
                char ans; cin >> ans;
                if (ans == 'y') {
                    gameStarted = false;
                    break;
                }
            }

            else {
                cout << "Unknown command.\n";
            }
        }
    }

    return 0;
}
