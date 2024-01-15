#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include "PhysicsObject.h"

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

    const unsigned num_points = 10;

    std::vector<PhysicsObject> entities;

    sf::Clock clock;
    sf::Clock spawn_clock = sf::Clock{};

    unsigned spawned_entities = 0;

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
        auto change_spawn_rate = spawn_clock.getElapsedTime();

        if (change_spawn_rate.asSeconds() > 1.f && spawned_entities < num_points) {
            entities.push_back(PhysicsObject({10.f, Height / 2}, 1));
            entities.back().apply_force({0, 9.8f});
            if (spawned_entities % 2 == 0)
                entities.back().set_velocity({100, 100});
            else {
                entities.back().set_velocity({100, -100});
            }
            spawned_entities++;
            spawn_clock.restart();
        }

        for (size_t i = 1; i <= 8; ++i) {
            auto sub_dt = dt.asSeconds() / static_cast<float>(i);

            for (auto& entity : entities) {
                entity.update_position(sub_dt);
            }
        }

        for (auto & entity : entities) {
            auto out_of_bounds_bottom = entity.pos().y + entity.radius() > window.getSize().y;
            auto out_of_bounds_top = entity.pos().y < 0;
            auto out_of_bounds_right = entity.pos().x + entity.radius() > window.getSize().x;
            auto out_of_bounds_left = entity.pos().x < 0;

            if (out_of_bounds_right) {
                entity.move_to({window.getSize().x - entity.radius(), entity.pos().y});
                entity.set_velocity(sf::Vector2f {-entity.vel().x, entity.vel().y} * .9f);
            } else if (out_of_bounds_left) {
                entity.move_to({entity.radius(), entity.pos().y});
                entity.set_velocity(sf::Vector2f {-entity.vel().x, entity.vel().y} * .9f);
            }

            if (out_of_bounds_bottom) {
                entity.move_to({entity.pos().x, window.getSize().y - entity.radius()});
                entity.set_velocity(sf::Vector2f {entity.vel().x, -entity.vel().y} * .9f);
            } else if (out_of_bounds_top) {
                entity.move_to({entity.pos().x, entity.radius()});
                entity.set_velocity(sf::Vector2f {entity.vel().x, -entity.vel().y} * .9f);
            }

            for (auto & other : entities) {
                if (&entity == &other) {
                    continue;
                }

                auto distance_between = distance(entity.pos(), other.pos());
                auto radius_sum = entity.radius() + other.radius();

                // AI Generated
                if (distance_between <= radius_sum) {
                    auto normal = (entity.pos() - other.pos()) / distance_between;
                    auto tangent = sf::Vector2f{ -normal.y, normal.x };

                    auto normal_dot = dot_product(entity.vel(), normal);
                    auto tangent_dot = dot_product(entity.vel(), tangent);

                    auto normal_vel = normal * normal_dot;
                    auto tangent_vel = tangent * tangent_dot;

                    entity.set_velocity((tangent_vel - normal_vel) * .9f);
                }

//                if (distance_between <= radius_sum) {
//                    auto normal = (entity.pos() - other.pos()) / distance_between;
//                    auto relative_velocity = entity.vel() - other.vel();
//                    auto impulse = normal * (2 * dot_product(relative_velocity, normal) / 2);
//
//                    entity.apply_impulse(impulse);
//                }
            }
        }


        window.clear();
        for (auto & entity : entities) {
            auto circleShape = sf::CircleShape{ entity.radius() };
            sf::Vertex velocityLine[] = {
                    sf::Vertex{entity.pos(), sf::Color::Red},
                    sf::Vertex{entity.pos() + entity.vel(), sf::Color::Red}
            };
            circleShape.setPosition(entity.pos() - sf::Vector2f{ entity.radius(), entity.radius() });
            std::cout << entity.pos().x << ", " << entity.pos().y << '\n';
            window.draw(circleShape);
            window.draw(velocityLine, 2, sf::Lines);
        }
        window.display();
    }
}