#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "PhysicsObject.hpp"
#include "Solver.hpp"

const unsigned Width = 800u;
const unsigned Height = 800u;

float dot_product(sf::Vector2f a, sf::Vector2f b)
{
    return a.x * b.x + a.y * b.y;
}

float distance(sf::Vector2f a, sf::Vector2f b)
{
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

int main()
{
    auto window = sf::RenderWindow{ { Width, Height }, "CMake SFML Project" };
    window.setFramerateLimit(60);

    Solver solver{ 8, window.getSize().x, window.getSize().y };
    solver.addRandomObjects(10);
    sf::Clock clock;
    sf::Clock spawnClock = sf::Clock{};

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
            sf::Vertex velocityLine[] = {
                    sf::Vertex{object.position(), sf::Color::Red},
                    sf::Vertex{object.position() + object.velocity(), sf::Color::Red}
            };
            circleShape.setPosition(object.position() - sf::Vector2f{ object.radius(), object.radius() });
            window.draw(circleShape);
            window.draw(velocityLine, 2, sf::Lines);
        }
        window.display();
    }
}