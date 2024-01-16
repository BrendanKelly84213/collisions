//
// Created by brendan on 15/01/24.
//

#ifndef CMAKESFMLPROJECT_SOLVER_HPP
#define CMAKESFMLPROJECT_SOLVER_HPP

#include <vector>
#include "PhysicsObject.hpp"

class Solver {
public:
    Solver() = default;
    Solver(const size_t substeps, const unsigned int width, const unsigned int height) : m_substeps(substeps), m_width(width), m_height(height) {}

    void addRandomObjects(unsigned int count);
    void addObject(const PhysicsObject& object);
    void update(float dt);
    void checkCollisions();
    void checkOutOfBounds();
    void applyGravity();
    void updateObjects(float dt);

    std::vector<PhysicsObject>& objects() { return m_objects; }

private:
    std::vector<PhysicsObject> m_objects;
    size_t m_substeps;
    unsigned int m_width;
    unsigned int m_height;
};


#endif //CMAKESFMLPROJECT_SOLVER_HPP
