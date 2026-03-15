#include <iostream>
using namespace std;
 
int main()
{
    // упаковка/розпаковка кольору в одну змінну
    unsigned int red, green, blue;
    unsigned int color;  // 4Бт     00000000 00000000 00000000 00000000
                         //         00000000 00011111 11101001 11101001  ?
    cout << "Enter a red component (dec) "<< endl;
    cin >> red;  // 31   00000000 00000000 00000000 00011111
    cout << "Enter a green component (dec) "<< endl;
    cin >> green;  // 233   00000000 00000000 00000000 11101001
    cout << "Enter a blue component (dec) "<< endl;
    cin >> blue;  // 242  00000000 00000000 00000000 11110010
    red = red << 16;    // 00000000 00011111 00000000 00000000
    green = green << 8; // 00000000 00000000 11101001 00000000 
                        // 00000000 00000000 00000000 11110010

    color = red | green | blue;  // 00000000 00011111 11101001 11110010   
    cout <<"#" <<hex << color << endl;  // hex   шістнадцяткове представлення числа

    // розпаковка кольору
    cout << "Enter a color (hex, # ff201b)    # ";
    cin >> hex >> color;  // 00000000 00011111 11101001 11110010
    red = color >> 16;    // 00000000 00000000 00000000 00011111

                        // &
                        // 00000000 00000000 00000000 11111111
    // маска = набір 0 або 1, який дозволяє позбутися зайвого

    green =  color >> 8 & 0xFF;  // 0x  -  число в 16-системі числення
    // 00000000 00000000 00000000 11101001
    blue = color & 0xFF;  // 00000000 00000000 00000000 11110010
    cout << dec << red << endl;  // dec 10, hex 16, oct 8
    cout << dec << green << endl;
    cout << dec << blue << endl;

 
    return 0;
}