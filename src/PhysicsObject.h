#pragma once

#include <SFML/Graphics.hpp>

class PhysicsObject {
private:
    sf::Vector2f m_current_pos;
    sf::Vector2f m_old_pos;
    sf::Vector2f m_velocity;
    sf::Vector2f m_accel;
    sf::Vector2f m_forces;
    float m_mass;
    bool m_fixed;
    size_t m_id;
    float m_radius;

public:
    PhysicsObject() = default;

    PhysicsObject(sf::Vector2f pos, float mass)
        : m_current_pos(pos), m_old_pos(pos), m_accel({0, 0}), m_forces({0, 0}), m_mass(mass),  m_fixed(false), m_id(0), m_radius(mass * 10.f)
    {
    }

    void apply_force(sf::Vector2f force)
    {
        m_forces += force;
    }

    void update_position(float dt)
    {
        if(m_fixed) 
            return;

        m_old_pos = m_current_pos;
        m_velocity += (m_forces / m_mass) * dt; 
        m_current_pos += m_velocity * dt;
    }

    void update_acceleration(float dt)
    {
        m_accel = m_forces / (m_mass * dt);
    }

    void update_velocity(float dt)
    {
        if(dt == 0)
            return;
        m_velocity = (m_current_pos - m_old_pos) / dt;
    }

    void accelerate(sf::Vector2f acc)
    {
        m_accel += acc;
    }

    void move(sf::Vector2f velocity)
    {
        if(m_fixed)
            return;
        m_current_pos += velocity;
    }

    void move_to(sf::Vector2f position)
    {
        m_current_pos = position;
    }

    void apply_impulse(sf::Vector2f impulse)
    {
        m_velocity += impulse / m_mass;
    }

    sf::Vector2f pos() const { return m_current_pos; }
    sf::Vector2f vel() const { return m_velocity; }
    sf::Vector2f accel() const { return m_accel; }
    bool fixed() const { return m_fixed; }
    void set_fixed(bool fixed) { m_fixed = fixed; }
    float mass() const { return m_mass; }
    float inverse_mass() const 
    {
        if(m_mass == 0)
            return 0;
        return 1 / m_mass;
    }
    size_t id() const { return m_id; }
    float radius() const { return m_radius; }
    void set_id(size_t id) { m_id = id; }
    void set_velocity(sf::Vector2f velocity) { m_velocity = velocity; }
};
