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
            object.setVelocity({object.velocity().x * -1, object.velocity().y});
        } else if (object.position().x + object.radius() > m_width) {
            object.setPosition({static_cast<float>(m_width + object.radius()), object.position().y});
            object.setVelocity({object.velocity().x * -1, object.velocity().y});
        }

        if (object.position().y - object.radius() < 0) {
            object.setPosition({object.position().x, object.radius()});
            object.setVelocity({object.velocity().x, object.velocity().y * -1});
        } else if (object.position().y + object.radius() > m_height) {
            object.setPosition({object.position().x, static_cast<float>(m_height - object.radius())});
            object.setVelocity({object.velocity().x, object.velocity().y * -1});
        }
    }
}

void Solver::addRandomObjects(unsigned int count)
{
    for (auto i = 0u; i < count; ++i) {
        auto x = static_cast<float>(rand() % m_width);
        auto y = static_cast<float>(rand() % m_height);
        for (auto& object : m_objects ) {
            auto distance = std::sqrt(std::pow(object.position().x - x, 2) + std::pow(object.position().y - y, 2));
            if (distance < object.radius() + 10) {
                x += object.radius() * 2 ;
                y += object.radius() * 2;
            }
        }
        auto mass = static_cast<float>(rand() % 50);
        auto object = PhysicsObject{ { x, y }, mass };
        object.setId(i);
        addObject(object);
    }
}

void Solver::update(float dt)
{
    for (size_t i = 0; i < m_substeps; ++i) {
        float subDt = dt / static_cast<float>(m_substeps);
        applyGravity();
        checkOutOfBounds();
        checkCollisions();
        updateObjects(subDt);
    }
}

void Solver::checkCollisions()
{
}

void Solver::addObject(PhysicsObject object)
{
    m_objects.push_back(object);
}

void Solver::applyGravity()
{
    for (auto& object : m_objects) {
        object.applyForce({0, 9800.f});
    }
}

void Solver::updateObjects(float dt)
{
    for (auto& object : m_objects) {
        object.update(dt);
    }
}
