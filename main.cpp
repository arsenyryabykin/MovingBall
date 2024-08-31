#include <iostream>
#include <cmath>
#include <vector>
#include "Resources.hpp"
#include "Body.hpp"

#define FPS 60
#define PPM 200
#define G 9.81

class Game
{
    public:
        Game() : window(sf::VideoMode(SCREEN_W, SCREEN_H), L"MovingEquations", sf::Style::Default),
                 shape(1, -6),
                 floor(sf::Vector2f(1280, 100))
        {
            window.setFramerateLimit(FPS);
            floor.setFillColor(sf::Color(255,0,230));
            floor.setPosition(0, 620);

             
        }

        void run()
        {
            sf::Clock clock;
            sf::Time timeSinceLastUpdate = sf::Time::Zero;
            sf::Time TimePerFrame = sf::seconds(1./FPS);
            bool repaint = false;

            while (window.isOpen())
            {

                ProcessEvents();
                timeSinceLastUpdate += clock.restart();
                while (timeSinceLastUpdate > TimePerFrame)
                {
                    timeSinceLastUpdate -= TimePerFrame;
                    repaint = true;
                    update(TimePerFrame);
                }
                if (repaint)
                    render();
                    
                //update(TimePerFrame);
                //render();
                

            }
        }
    private:

        sf::RenderWindow window;
        sf::CircleShape point;
        Body shape;
        sf::RectangleShape floor;
        std::vector<sf::CircleShape> points;

        void ProcessEvents()
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                // Закрыть окно при нажатии на крестик
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Space)
                    {
                        if (shape.isMove == false)
                        {
                            shape.isMove = true;
                        }      
                    }
                }
            }

        }
        void update(sf::Time deltaTime)
        {


            if (shape.isMove == true)
            {
                //shape.v.y += shape.v0.y * deltaTime.asSeconds() + G * (deltaTime.asSeconds() * deltaTime.asSeconds()) / 2;
                shape.v.y += G * deltaTime.asSeconds();
                std::cout << shape.v.y << std::endl;
                shape.move(shape.v.x, shape.v.y);

                sf::CircleShape point(1);
                point.setPosition(shape.getPosition());
                points.push_back(point);
            }
            if (isCollide() and shape.isMove)
            {
                    shape.v.y = -0.9 * shape.v.y;
                /*else
                {
                    shape.v.y = 0;
                    shape.isMove = false;
                }*/
            }


        };
        void render()
        {
            window.clear();
            //window.draw(shape1);
            window.draw(shape);
            window.draw(floor);
            for(auto el : points)
                window.draw(el);
            window.display();
        }

        bool isCollide()
        {
            //sf::FloatRect a = floor.getGlobalBounds();
            //sf::FloatRect b = shape.getGlobalBounds();
            return shape.getGlobalBounds().intersects(floor.getGlobalBounds());
        }
};

int main()
{
    Game game;
    game.run();

    return 0;
}