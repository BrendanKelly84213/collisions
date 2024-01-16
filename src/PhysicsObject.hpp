//
// Created by brendan on 15/01/24.
//

#ifndef PHYSICSOBJECT_HPP
#define PHYSICSOBJECT_HPP

#include <SFML/System.hpp>

class PhysicsObject {
public:
    PhysicsObject() = default;

    PhysicsObject(sf::Vector2f pos, float mass, float coefficientOfRestitution = 1.f)
            : m_currentPos(pos), m_oldPos(pos), m_accel({0, 0}), m_forces({0, 0}), m_mass(mass), m_fixed(false), m_id(0), m_radius(mass), m_coefficientOfRestitution(coefficientOfRestitution)
    {
    }

    void applyForce(sf::Vector2f force);
    void update(float dt);
    void move(sf::Vector2f velocity);

    void setPosition(sf::Vector2f position) { m_currentPos = position; }
    void setVelocity(sf::Vector2f velocity) { m_velocity = velocity; }
    void setFixed(bool fixed) { m_fixed = fixed; }
    void setId(size_t id) { m_id = id; }

    sf::Vector2f position() const { return m_currentPos; }
    sf::Vector2f velocity() const { return m_velocity; }
    float mass() const { return m_mass; }
    bool fixed() const { return m_fixed; }
    size_t id() const { return m_id; }
    float radius() const { return m_radius; }
    float coefficientOfRestitution() const { return m_coefficientOfRestitution; }

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
    float m_coefficientOfRestitution;
};

#endif //PHYSICSOBJECT_HPP