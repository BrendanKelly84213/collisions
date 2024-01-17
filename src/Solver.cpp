//
// Created by brendan on 15/01/24.
//

#include "Solver.hpp"
#include <iostream>
#include <valarray>

void Solver::checkOutOfBounds()
{
    for (auto& object : m_objects) {
        if (object.position().x - object.radius() < 0) {
            object.setPosition({object.radius(), object.position().y});
            object.setVelocity(sf::Vector2f{object.velocity().x * -1, object.velocity().y} * object.coefficientOfRestitution());
        } else if (object.position().x + object.radius() > static_cast<float>(m_width)) {
            object.setPosition({static_cast<float>(m_width) - object.radius(), object.position().y});
            object.setVelocity(sf::Vector2f{object.velocity().x * -1, object.velocity().y} * object.coefficientOfRestitution());
        }

        if (object.position().y - object.radius() < 0) {
            object.setPosition({object.position().x, object.radius()});
            object.setVelocity(sf::Vector2f{object.velocity().x, object.velocity().y * -1} * object.coefficientOfRestitution());
        } else if (object.position().y + object.radius() > static_cast<float>(m_height)) {
            object.setPosition({object.position().x, static_cast<float>(m_height) - object.radius()});
            object.setVelocity(sf::Vector2f{object.velocity().x, object.velocity().y * -1} * object.coefficientOfRestitution());
        }
    }
}

void Solver::addRandomObjects(const unsigned int count)
{
    for (auto i = 0u; i < count; ++i) {
        auto x = static_cast<float>(rand() % m_width);
        auto y = static_cast<float>(rand() % m_height);
        for (auto& object : m_objects ) {
            const auto distance = std::sqrt(std::pow(object.position().x - x, 2) + std::pow(object.position().y - y, 2));
            if (distance < object.radius() + 10) {
                x += object.radius() * 2 ;
                y += object.radius() * 2;
            }
        }
        const auto mass = static_cast<float>(rand() % 50) + 1;
        auto object = PhysicsObject{ { x, y }, mass };
        object.setVelocity({static_cast<float>(rand() % 100), static_cast<float>(rand() % 100)});
        object.setId(i);
        addObject(object);
    }
}

void Solver::update(const float dt)
{
    for (size_t i = 0; i < m_substeps; ++i) {
        const float subDt = dt / static_cast<float>(m_substeps);
        checkOutOfBounds();
        checkCollisions();
        updateObjects(subDt);
    }
}

void Solver::checkCollisions()
{
    for (size_t i = 0; i < m_objects.size(); ++i) {
        auto& object = m_objects[i];
        auto dotProduct = [](const sf::Vector2f& a, const sf::Vector2f& b) {
            return a.x * b.x + a.y * b.y;
        };
        for (size_t j = i + 1; j < m_objects.size(); ++j) {
            auto& other = m_objects[j];
            const auto distance = static_cast<float>(std::sqrt(std::pow(object.position().x - other.position().x, 2) + std::pow(object.position().y - other.position().y, 2)));
            if (distance < object.radius() + other.radius()) {
                // Pulled straight from wikipedia: https://en.wikipedia.org/wiki/Elastic_collision
                const auto newObjectVelocity = static_cast<float>((2 * other.mass() / (object.mass() + other.mass())) * ((dotProduct(object.velocity() - other.velocity(), object.position() - other.position()) / std::pow(distance, 2)))) * (object.position() - other.position());
                const auto newOtherVelocity = static_cast<float>((2 * object.mass() / (object.mass() + other.mass())) * ((dotProduct(other.velocity() - object.velocity(), other.position() - object.position()) / std::pow(distance, 2)))) * (other.position() - object.position());
                // Move the objects so they are no longer colliding
                const auto overlap = (object.radius() + other.radius()) - distance;
                const auto direction = (object.position() - other.position()) / distance;
                object.setPosition(object.position() + direction * overlap * 0.5f);
                other.setPosition(other.position() - direction * overlap * 0.5f);
                object.setVelocity((object.velocity() - newObjectVelocity) * object.coefficientOfRestitution());
                other.setVelocity((other.velocity() - newOtherVelocity) * object.coefficientOfRestitution());
            }
        }
    }
}

void Solver::addObject(const PhysicsObject& object)
{
    m_objects.push_back(object);
}

void Solver::applyGravity()
{
    for (auto& object : m_objects) {
        object.applyForce({0, 9800.f});
    }
}

void Solver::updateObjects(const float dt)
{
    for (auto& object : m_objects) {
        object.update(dt);
    }
}
