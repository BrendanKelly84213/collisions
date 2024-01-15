//
// Created by brendan on 15/01/24.
//

#include "PhysicsObject.hpp"

void PhysicsObject::applyForce(sf::Vector2f force)
{
    m_forces += force;
}

void PhysicsObject::updatePosition(float dt)
{
    if(m_fixed)
        return;

    m_oldPos = m_currentPos;
    m_velocity += (m_forces / m_mass) * dt;
    m_currentPos += m_velocity * dt;
}

void PhysicsObject::updateAcceleration(float dt)
{
    m_accel = m_forces / (m_mass * dt);
}

void PhysicsObject::updateVelocity(float dt)
{
    if(dt == 0)
        return;
    m_velocity = (m_currentPos - m_oldPos) / dt;
}

void PhysicsObject::accelerate(sf::Vector2f acc)
{
    m_accel += acc;
}

void PhysicsObject::move(sf::Vector2f velocity)
{
    if(m_fixed)
        return;
    m_currentPos += velocity;
}

void PhysicsObject::moveTo(sf::Vector2f position)
{
    m_currentPos = position;
}

void PhysicsObject::applyImpulse(sf::Vector2f impulse)
{
    m_velocity += impulse / m_mass;
}

float PhysicsObject::inverseMass() const
{
    if(m_mass == 0)
        return 0;
    return 1 / m_mass;
}
