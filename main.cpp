#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>
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
    int colored[LINES];
    int score = 0;
    Font font;
    font.loadFromFile("Poppins-Regular.ttf");
    Text scoretext;
    scoretext.setFont(font);
    scoretext.setFillColor(Color::Black);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed) {
                for (int i = 0; i < LINES; i++)
                {

                    if (colored[i] >= 0 && colored[i] <= RECTANGLES)
                    {
                        if (event.mouseButton.x < rectangles[i][colored[i]].getPosition().x + rectangles[i][colored[i]].getSize().x
                            && event.mouseButton.x > rectangles[i][colored[i]].getPosition().x
                            && event.mouseButton.y < rectangles[i][colored[i]].getPosition().y + rectangles[i][colored[i]].getSize().y
                            && event.mouseButton.y > rectangles[i][colored[i]].getPosition().y
                            && rectangles[i][colored[i]].getFillColor() != Color(237, 237, 237))
                        {
                            score++;
                            rectangles[i][colored[i]].setFillColor(Color(237, 237, 237));

                        }
                    }
                }
            }
        }
        window.clear();
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
                        if (colored[i] >= 0 && colored[i] <= RECTANGLES)
                        {
                            if (rectangles[i][colored[i]].getPosition().y + rectangles[i][colored[i]].getSize().y == 0)
                            {
                                rectangles[i][colored[i]].setFillColor(Color::White);
                            }
                        }
                    }
                }
            }

            clock.restart();
        }

        for (int i = 0; i < LINES; i++)
            for (int i2 = 0; i2 < RECTANGLES; i2++)
                window.draw(rectangles[i][i2]);
        scoretext.setString("Score: " + std::to_string(score));

        window.draw(scoretext);
        window.display();
    }

    return 0;
}