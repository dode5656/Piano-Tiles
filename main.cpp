#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#define RECTANGLES 4
#define LINES 8

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(900, 900), "Piano Tiles");
    Texture planeTexture;
    Texture tileTexture;
    planeTexture.loadFromFile("plane.png");
    tileTexture.loadFromFile("pianotile.png");
    Sprite plane(planeTexture);
    Sprite plane2(planeTexture);
    std::vector<Sprite> tiles(LINES, Sprite(tileTexture));
    Clock clock;
    plane.setScale((float)window.getSize().x / (float)plane.getTexture()->getSize().x, (float)window.getSize().y / (float)plane.getTexture()->getSize().y);
    plane2.setScale((float)window.getSize().x / (float)plane2.getTexture()->getSize().x, (float)window.getSize().y / (float)plane2.getTexture()->getSize().y);
    float rectanglesX[LINES][RECTANGLES];
    float rectanglesY[LINES][RECTANGLES];
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear();
        if (clock.getElapsedTime().asSeconds() >= 0.03f) {
            for (int i = 0; i < LINES; i++)
            {
                for (int j = 0; j < RECTANGLES; j++)
                {
                    if (i <= 4)
                    {
                        rectanglesX[i][j] = ((plane.getPosition().x + plane.getTexture()->getSize().x * plane.getScale().x) / 4) * j;
                        rectanglesY[i][j] = ((plane.getPosition().y + plane.getTexture()->getSize().y * plane.getScale().y) / 4) * j;
                    }
                    else
                    {
                        rectanglesX[i][j] = ((plane2.getPosition().x + plane2.getTexture()->getSize().x * plane2.getScale().x) / 4) * j;
                        rectanglesY[i][j] = ((plane2.getPosition().y + plane.getTexture()->getSize().y * plane.getScale().y) / 4) * j;
                    }
                }
            }
            int i = 0;
            for (Sprite tile : tiles) {
                tile.setPosition(rectanglesX[i][rand() % 4], rectanglesY[i][rand() % 4]);
                tile.setScale(window.getSize().x / LINES/2, window.getSize().y / LINES/2);
                window.draw(tile);
                i++;
            }
            if (plane.getPosition().y + plane.getTexture()->getSize().y*plane.getScale().y <= 0)
                plane.setPosition(plane.getPosition().x, window.getSize().y);
            if (plane.getPosition().y <= 0)
                plane2.setPosition(plane.getPosition().x, plane.getPosition().y + (plane.getTexture()->getSize().y * plane.getScale().y) - 10);
            else
                plane2.setPosition(plane2.getPosition().x, plane2.getPosition().y - 10);
            if (plane2.getPosition().y + plane2.getTexture()->getSize().y*plane2.getScale().y <= 0)
                plane2.setPosition(plane2.getPosition().x, window.getSize().y);
            plane.setPosition(plane.getPosition().x, plane.getPosition().y - 10);
            clock.restart();
        }
        window.draw(plane2);
        window.draw(plane);
        window.display();
    }

    return 0;
}