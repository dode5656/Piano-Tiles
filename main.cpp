#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#define RECTANGLES 4
#define LINES 6

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(900, 900), "Piano Tiles");
    Clock clock;
    RectangleShape rectangles[LINES][RECTANGLES];
    for (int i = 0; i < LINES; i++) {
        for (int i2 = 0; i2 < RECTANGLES; i2++) {
            rectangles[i][i2].setSize(Vector2f(window.getSize().x / RECTANGLES, window.getSize().y / LINES * 2));
            rectangles[i][i2].setPosition(window.getSize().x / RECTANGLES * i2, (window.getSize().y / LINES * i) * 2);
            rectangles[i][i2].setOutlineColor(Color::Black);
            rectangles[i][i2].setOutlineThickness(2);
            rectangles[i][i2].setFillColor(Color::White);
        }
    }
    int bottomline = LINES - 1;
    int colored[LINES] = {0};

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear();
        float line = 1;
        float counter = 1;
        /*for (RectangleShape rectangle : rectangles)
        {
            rectangle.setFillColor(Color(255,255,255));
            rectangle.setSize(Vector2f(window.getSize().x/RECTANGLES, window.getSize().y/(LINES/2.0f)));
            rectangle.setOutlineColor(Color::Black);
            rectangle.setOutlineThickness(2);
            rectangle.setPosition((window.getSize().x/RECTANGLES) * counter, window.getSize().y / line);
            if (counter == 4.0f)
            {
                line++;
                counter = 1;
            }
            if (line == 8.0f)
                line = 1;
            counter++;
            window.draw(rectangle);
        }*/
        if (clock.getElapsedTime().asSeconds() >= 0.03f) {
            for (int i = 0; i < LINES; i++) {
                for (int i2 = 0; i2 < RECTANGLES; i2++) {
                    if (rectangles[i][i2].getPosition().y + rectangles[i][i2].getSize().y <= 0)
                    {
                        for (int j = 0; j < RECTANGLES; j++)
                            rectangles[i][j].setPosition(rectangles[i][j].getPosition().x, rectangles[bottomline][0].getPosition().y+rectangles[i][j].getSize().y);
                        bottomline = i;
                        int random = rand() % RECTANGLES;
                        rectangles[i][random].setFillColor(Color(97, 155, 255));
                        colored[i] = random;
                    }
                    rectangles[i][i2].setPosition(rectangles[i][i2].getPosition().x, rectangles[i][i2].getPosition().y - 10);
                    for (int i = 0; i < LINES; i++) {
                        if (rectangles[i][colored[i]].getPosition().y + rectangles[i][colored[i]].getSize().y == 0)
                        {
                            rectangles[i][colored[i]].setFillColor(Color::White);
                            std::cout << "test" << std::endl;
                        }
                    }
                }
            }

            clock.restart();
        }

        for (int i = 0; i < LINES; i++)
            for (int i2 = 0; i2 < RECTANGLES; i2++)
                window.draw(rectangles[i][i2]);
        window.display();
    }

    return 0;
}