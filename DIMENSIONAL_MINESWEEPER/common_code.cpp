#pragma once

#include <iostream> // for cout, cin
#include <iomanip>  // for setw
#include <cstdlib>  // for system("cls")
#include <cstring>  // for memset
#include <cstdio>   // For remove()
#include <conio.h>  // _kbhit(), _getch()
#include <chrono>   // for sleep
#include <thread>   // for sleep too
#include "io.h"     // for _filelength, _fileno
#include "str.cpp"

using namespace std;

enum User_State { USER, ADMIN, CREATOR };
enum Message_Type { TEXT, ADMIN_ACCESS, CREATOR_ACCESS, POST };

struct Message {
    int from_id;
    int to_id;
    int id; // chat ID
    int time; // time of message
    int date; // date of message
    char message[1000];
    Message_Type type;
};

struct User {
    int minecoins; // number of minecoins
    int games_played_1D; // number of games played (1D)
    int games_played_2D; // number of games played (2D)
    int games_played_3D; // number of games played (3D)
    int games_played_4D; // number of games played (4D)
    int experience; // user experience
    int total_experience; // user total experience
    int level;    // user level
    int win_strike; // number of consecutive wins
    int id;      // user ID
    int higher_score; // highest score
    User_State state; // user state, default is USER
    Message** ptrMs; // array of pointers to messages
    int Size_of_ptrMs;     // total size of the array
    int Count_of_ptrMs;    // current number of users
    int Block_of_ptrMs = 10;    // block size for dynamic allocation
    char username[50];
    char password[50];
};

struct User_for_safe {
    int minecoins; // number of minecoins
    int games_played_1D; // number of games played (1D)
    int games_played_2D; // number of games played (2D)
    int games_played_3D; // number of games played (3D)
    int games_played_4D; // number of games played (4D)
    int experience; // user experience
    int total_experience; // user total experience
    int level;    // user level
    int win_strike; // number of consecutive wins
    int id;      // user ID
    int higher_score; // highest score
    User_State state; // user state, default is USER
    // Message** ptrMs; // array of pointers to messages // not need
    int Size_of_ptrMs;     // total size of the array
    int Count_of_ptrMs;    // current number of users
    int Block_of_ptrMs = 10;    // block size for dynamic allocation
    char username[50];
    char password[50];
};

struct ArrayUsers {
    User** ptrUs;  // array of pointers to users
    Message** ptrMs; // array of pointers to messages
    int SizeUs;     // total size of the array
    int CountUs;    // current number of users
    int SizeMs;     // total size of the array
    int CountMs;    // current number of users
    int Block = 10;    // block size for dynamic allocation
};

User_for_safe Convert_User_to_UserForSafe(const User& user) {
    User_for_safe ufs;

    ufs.minecoins = user.minecoins;
    ufs.games_played_1D = user.games_played_1D;
    ufs.games_played_2D = user.games_played_2D;
    ufs.games_played_3D = user.games_played_3D;
    ufs.games_played_4D = user.games_played_4D;
    ufs.experience = user.experience;
    ufs.total_experience = user.total_experience;
    ufs.level = user.level;
    ufs.win_strike = user.win_strike;
    ufs.id = user.id;
    ufs.higher_score = user.higher_score;
    ufs.state = user.state;
    ufs.Size_of_ptrMs = user.Size_of_ptrMs;
    ufs.Count_of_ptrMs = user.Count_of_ptrMs;
    ufs.Block_of_ptrMs = user.Block_of_ptrMs;
    strncpy_s(ufs.username, user.username, sizeof(ufs.username));
    strncpy_s(ufs.password, user.password, sizeof(ufs.password));

    return ufs;
}

User* Convert_UserForSafe_to_User(const User_for_safe& ufs) {
    User* user = new User;

    user->minecoins = ufs.minecoins;
    user->games_played_1D = ufs.games_played_1D;
    user->games_played_2D = ufs.games_played_2D;
    user->games_played_3D = ufs.games_played_3D;
    user->games_played_4D = ufs.games_played_4D;
    user->experience = ufs.experience;
    user->total_experience = ufs.total_experience;
    user->level = ufs.level;
    user->win_strike = ufs.win_strike;
    user->id = ufs.id;
    user->higher_score = ufs.higher_score;
    user->state = ufs.state;
    user->Size_of_ptrMs = ufs.Size_of_ptrMs;
    user->Count_of_ptrMs = ufs.Count_of_ptrMs;
    user->Block_of_ptrMs = ufs.Block_of_ptrMs;
    strncpy_s(user->username, ufs.username, sizeof(user->username));
    strncpy_s(user->password, ufs.password, sizeof(user->password));

    return user;
}

void Menu(char menu[][50], int row)
{
    for (int i = 0; i < row; i++)
        cout << menu[i] << endl;
}

int Get_position_of_user(const ArrayUsers& au, const char* username) {
    int pos = -1;
    for (int i = 0; i < au.CountUs; i++) {
        if (strcmp(au.ptrUs[i]->username, username) == 0) {
            pos = i;
            break;
        }
    }
    return pos;
}

int Get_position_of_user(const ArrayUsers& au, const int id) {
    int pos = -1;
    for (int i = 0; i < au.CountUs; i++) {
        if (au.ptrUs[i]->id == id) {
            pos = i;
            break;
        }
    }
    return pos;
}

void Get_Game_Password(char *password) {
    FILE* f = nullptr;
    fopen_s(&f, "game_password.txt", "ab");
    if (_filelength(_fileno(f)) == 0) {
        strcpy(password, "GAME_PASSWORD_NOT_INSTALLED"); // if somethig will go wrong, password will be exist
        fwrite(password, sizeof(char), 50, f); // writing game_password into a file
    } else {
        fclose(f);
        fopen_s(&f, "game_password.txt", "rb");
        fread(password, sizeof(char), 50, f);
    }
    fclose(f);
}

char* Int_to_str(int num)
{
    int length = 0;
    int temp = num;
    if (num < 0) {
        length++; // for negative sign
        temp = -temp; // make positive for length calculation
    }
    
    do {
        length++;
        temp /= 10;
    } while (temp != 0);

    char* str = new char[length + 1]; // +1 for null terminator
    str[length] = '\0'; // null-terminate the string

    int is_negative = 0;

    if (num < 0) {
        str[0] = '-';
        num = -num; // make positive for conversion
        is_negative = 1;
    }

    for (int i = length - 1; i >= (is_negative == 1 ? 1 : 0); i--) {
        str[i] = (num % 10) + '0'; // convert digit to character
        num /= 10;
    }

    return str;
}

void Load_Users_Data(ArrayUsers& au) {
    FILE* f = nullptr;
    fopen_s(&f, "users_messages.txt", "rb");  // open the file for reading
    if (f == nullptr) {
        fclose(f);
        return;
    }

    FILE* f2 = nullptr;
    fopen_s(&f2, "users.txt", "rb");  // open the file for reading
    if (f2 == nullptr) {
        return;
    }

    int length2 = _filelength(_fileno(f2)); // get the file length in bytes
    length2 = length2 / sizeof(User_for_safe);  // calculate the number of users in the file

    int length = _filelength(_fileno(f)); // get the file length in bytes
    length = length / sizeof(Message);  // calculate the number of users in the file

    if (length2 != 0) {
        if (au.ptrUs != nullptr) {
            for (int i = 0; i < au.CountUs; i++) {
                if (au.ptrUs[i] != nullptr) delete au.ptrUs[i];
                au.ptrUs[i] = nullptr;
            }
            delete[] au.ptrUs; // free previous data
            au.ptrUs = nullptr;
        }

        au.CountUs = length2;
        au.SizeUs = au.CountUs + au.Block;

        User** temp2 = new User*[au.SizeUs];
        au.ptrUs = temp2;

        for (int i = 0; i < au.CountUs; i++) {  // read user data from the file
            User_for_safe usf;
            fread(&usf, sizeof(User_for_safe), 1, f2);
            au.ptrUs[i] = Convert_UserForSafe_to_User(usf);
        }

        if (length != 0) {
            for (int i = 0; i < au.CountUs; i++) {
                if (au.ptrUs[i]->Count_of_ptrMs != 0) {
                    if (au.ptrUs[i]->ptrMs != nullptr) {
                        for (int j = 0; j < au.ptrUs[i]->Count_of_ptrMs; j++) {
                            delete au.ptrUs[i]->ptrMs[j];
                        }
                        delete [] au.ptrUs[i]->ptrMs;
                    }

                    Message** temp = new Message*[au.ptrUs[i]->Size_of_ptrMs];
                    au.ptrUs[i]->ptrMs = temp;

                    for (int j = 0; j < au.ptrUs[i]->Count_of_ptrMs; j++) {
                        au.ptrUs[i]->ptrMs[j] = new Message;
                        fread(au.ptrUs[i]->ptrMs[j], sizeof(Message), 1, f);
                    }
                } else {
                    au.ptrUs[i]->ptrMs = nullptr;
                }
            }
        }
    } else {
        au.ptrUs = nullptr;
        au.SizeUs = 0;
        au.CountUs = 0;
    }
    fclose(f);
    fclose(f2); // close the file
}

void Clear_File() {
    FILE* f = nullptr;
    fopen_s(&f, "users.txt", "wb");  // open the file for writing (to clear it)
    if (f == nullptr) {
        return;
    }
    fclose(f); // close the file after clearing it
}

void Fill_File_With_Users_Data(ArrayUsers& au) {
    Clear_File(); // clear the file before writing new data
    FILE* f = nullptr;
    fopen_s(&f, "users_messages.txt", "ab");  // open the file for appending
    if (f == nullptr) {
        return;
    }
    // cout << "chek" << endl;
    FILE* f2 = nullptr;
    fopen_s(&f2, "users.txt", "ab");  // open the file for appending
    if (f2 == nullptr) {
        system("cls");
        cout << "error" << endl;
        system("pause");
        return;
    }

    if (au.ptrUs == nullptr || au.CountUs == 0) {
        fclose(f2);
        return; // no users to write
    }
    for (int i = 0; i < au.CountUs; i++) {
        if (!(au.ptrUs[i]->ptrMs == nullptr || au.ptrUs[i]->Count_of_ptrMs == 0)) {
            for (int j = 0; j < au.CountUs; j++) {
                fwrite(au.ptrUs[i]->ptrMs[j], sizeof(Message), 1, f);
            }
        }
        User_for_safe ufs = Convert_User_to_UserForSafe(*au.ptrUs[i]);
        fwrite(&ufs, sizeof(User_for_safe), 1, f2); // write each user to the file
    }
    fclose(f);
    fclose(f2); // close the file
    return;
}
