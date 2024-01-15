//
// Created by brendan on 15/01/24.
//

#ifndef PHYSICSOBJECT_HPP
#define PHYSICSOBJECT_HPP

#include <SFML/System.hpp>

class PhysicsObject {
public:
    PhysicsObject() = default;

    PhysicsObject(sf::Vector2f pos, float mass)
            : m_currentPos(pos), m_oldPos(pos), m_accel({0, 0}), m_forces({0, 0}), m_mass(mass), m_fixed(false), m_id(0), m_radius(mass * 10.f)
    {
    }

    void applyForce(sf::Vector2f force);
    void updatePosition(float dt);
    void updateAcceleration(float dt);
    void updateVelocity(float dt);
    void accelerate(sf::Vector2f acc);
    void move(sf::Vector2f velocity);
    void moveTo(sf::Vector2f position);
    void applyImpulse(sf::Vector2f impulse);

    void setVelocity(sf::Vector2f velocity) { m_velocity = velocity; }
    void setFixed(bool fixed) { m_fixed = fixed; }
    void setId(size_t id) { m_id = id; }

    float inverseMass() const;
    sf::Vector2f pos() const { return m_currentPos; }
    sf::Vector2f vel() const { return m_velocity; }
    sf::Vector2f accel() const { return m_accel; }
    bool fixed() const { return m_fixed; }
    float mass() const { return m_mass; }
    size_t id() const { return m_id; }
    float radius() const { return m_radius; }

private:
    sf::Vector2f m_currentPos;
    sf::Vector2f m_oldPos;
    sf::Vector2f m_velocity;
    sf::Vector2f m_accel;
    sf::Vector2f m_forces;
    float m_mass;
    bool m_fixed;
    size_t m_id;
    float m_radius;
};

#endif //PHYSICSOBJECT_HPP