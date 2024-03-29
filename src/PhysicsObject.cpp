//
// Created by brendan on 15/01/24.
//

#include "PhysicsObject.hpp"

void PhysicsObject::applyForce(const sf::Vector2f force)
{
    m_forces += force;
}

void PhysicsObject::update(const float dt)
{
    if(m_fixed)
        return;

    m_oldPos = m_currentPos;
    m_velocity += (m_forces / m_mass) * dt;
    m_currentPos += m_velocity * dt;
    m_forces = {};
}

void PhysicsObject::move(const sf::Vector2f velocity)
{
    if(m_fixed)
        return;
    m_currentPos += velocity;
}
