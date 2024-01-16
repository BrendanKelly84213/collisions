#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "PhysicsObject.hpp"
#include "Solver.hpp"

const unsigned Width = 800u;
const unsigned Height = 800u;

int main()
{
    auto window = sf::RenderWindow{ { Width, Height }, "Collisions!" };
    window.setFramerateLimit(60);

    Solver solver{ 16, window.getSize().x, window.getSize().y };
    solver.addRandomObjects(10);
    sf::Clock clock;

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        auto dt = clock.restart();
        solver.update(dt.asSeconds());

        auto objects = solver.objects();
        window.clear();
        for (auto& object : objects) {
            auto circleShape = sf::CircleShape{ object.radius() };
            circleShape.setPosition(object.position() - sf::Vector2f{ object.radius(), object.radius() });
            window.draw(circleShape);
        }
        window.display();
    }
}