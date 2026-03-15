// MSYS2 Terminal
// cd /c/Users/maxim/OneDrive/Документы/Progranimg/c++/c++/4D_MINESWEEPER && g++ main.cpp -o sfml_test -lsfml-graphics -lsfml-window -lsfml-system && ./sfml_test

#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    // Create window
    RenderWindow window(VideoMode(800, 600), "SFML Test");

    // Create a circle shape
    RectangleShape shape(Vector2f(100, 100)); // create a rectangle shape with size 100x100
    shape.setOrigin(50, 50); // set the origin to the center of the rectangle
    shape.setOutlineThickness(5); // set the outline thickness
    shape.setOutlineColor(Color::Red); // set the outline color to red
    shape.setPosition(375, 275); // center the circle in the window
    shape.setFillColor(Color::Orange); // set the fill color to orange

    // Main loop
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();        // clear the window with black color
        window.draw(shape);    // draw the shape
        window.display();      // display the contents of the window
    }

    return 0;
}
