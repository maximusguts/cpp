#include <iostream>
#include <thread>

using namespace std;
using namespace chrono;
using namespace this_thread;

void draw_cubes(int n) {
    if (n == 1) {
        cout << 
        "   ______\n"
        "  /  ●  /|\n"
        " /_●_●_/ |\n"
        "|     |  |\n"
        "|     |● |\n"
        "|  ●  | ●|\n"
        "|     | /\n"
        "|_____|/\n";
    } else if (n == 2) {
        cout << 
        "   ______\n"
        "  /  ●  /|\n"
        " /_____/ |\n"
        "|     | ●|\n"
        "| ●   |●●|\n"
        "|     |● |\n"
        "|   ● | /\n"
        "|_____|/\n";
    } else if (n == 3) {
        cout << 
        "   ______\n"
        "  /  ●  /|\n"
        " /_●___/ |\n"
        "|     | ●|\n"
        "| ●   |●●|\n"
        "|  ●  |●●|\n"
        "|   ● |●/\n"
        "|_____|/\n";
    } else if (n == 4) {
        cout << 
        "   ______\n"
        "  /● ● ●/|\n"
        " /_●_●_/ |\n"
        "|     |  |\n"
        "| ● ● |  |\n"
        "| ● ● | /\n"
        "|_____|/\n";
    } else if (n == 5) {
        cout << 
        "   ______\n"
        "  /● ● ●/|\n"
        " /●_●_●/ |\n"
        "|     | ●|\n"
        "| ● ● |● |\n"
        "|  ●  | ●|\n"
        "| ● ● | /\n"
        "|_____|/\n";
    } else if (n == 6) {
        cout << 
        "   ______\n"
        "  /  ●  /|\n"
        " /_●___/ |\n"
        "|     | ●|\n"
        "| ● ● |● |\n"
        "| ● ● | ●|\n"
        "| ● ● | /\n"
        "|_____|/\n";
    }
}

int main()
{
    int total_p1 = 0;
    int total_p2 = 0;

    srand(time(0));
    cout << "Welcome to the game of cubes!\n\n";
    sleep_for(milliseconds(2000));
    cout << "Player 1 and Player 2 will take turns throwing two cubes.\n";
    sleep_for(milliseconds(2000));
    cout << "The cubes will be thrown three times.\n\n";
    sleep_for(milliseconds(2000));
    cout << "Press any key to start the game...\n";
    cin.get();
    sleep_for(milliseconds(1000));
    cout << "Starting the game...\n\n";
    sleep_for(milliseconds(1000));
    for (int i = 0; i < 3; i++)
    {
        cout << "\nRound " << i + 1 << "\n\n";
        sleep_for(milliseconds(500));
        
        cout << "\nPlayer 1, throw a cubes: (preess any key)" << endl;
        cin.get();
        cout << "trhowing cubes... (enter to stop)";
        cin.get();
        int player1_throw = (rand() % 6 + 1) * 10 + rand() % 6 + 1;
        
        sleep_for(milliseconds(500));
        
        int n1p1 = player1_throw / 10;
        int n2p1 = player1_throw % 10;

        draw_cubes(n1p1);
        draw_cubes(n2p1);

        cout << "\nPlayer 1, your score is: " << n1p1 << " + " << n2p1 << " = " << n1p1 + n2p1 << endl;
        total_p1 += n1p1 + n2p1;
        cout << "Your total score is: " << total_p1 << endl;
        sleep_for(milliseconds(1000));

        cout << "\nPlayer 2, throw a cubes: (preess any key)" << endl;
        cin.get();
        cout << "trhowing cubes... (enter to stop)";
        cin.get();
        int player2_throw = (rand() % 6 + 1) * 10 + rand() % 6 + 1;
        
        sleep_for(milliseconds(500));
        
        int n1p2 = player2_throw / 10;
        int n2p2 = player2_throw % 10;

        draw_cubes(n1p2);
        draw_cubes(n2p2);

        cout << "\nPlayer 2, your score is: " << n1p2 << " + " << n2p2 << " = " << n1p2 + n2p2 << endl;
        total_p2 += n1p2 + n2p2;
        cout << "Your total score is: " << total_p2 << endl;
        sleep_for(milliseconds(1000));
    }

    sleep_for(milliseconds(1000));
    cout << "\n\nFinal results:\n";
    sleep_for(milliseconds(1000));
    cout << "Player 1 total score: " << total_p1 << endl;
    sleep_for(milliseconds(1000));
    cout << "Player 2 total score: " << total_p2 << endl;
    sleep_for(milliseconds(2000));
    
    if (total_p1 > total_p2) {
        cout << "\nPlayer 1 wins!\n";
    } else if (total_p2 > total_p1) {
        cout << "\nPlayer 2 wins!\n";
    } else {
        cout << "\nIt's a tie!\n";
    }

    sleep_for(milliseconds(2000));
    cout << "\n\nThank you for playing!\n";
    sleep_for(milliseconds(1000));
    cout << "Press any key to exit...\n";
    cin.get();
    cout << "\n\nThe game is over!\n";
    sleep_for(milliseconds(1000));

    return 0;
}