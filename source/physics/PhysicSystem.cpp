//
// Created by edgar on 27/11/2021.
//

#include "PhysicSystem.hpp"


void PhysicSystem::update(TimeStep delta)
{
    // SUM ALL FORCES
    for(auto& body : m_rigidBodies)
    {
        body->applyForces();
    }

    // UPDATE POSITIONS
    for(auto& body : m_rigidBodies)
    {
        body->update(delta);
    }

    // SOLVE COLLISON AND UPDATE TRANSFORMS IF NECESSARY
    for(auto& body : m_rigidBodies)
    {
        body->handleCollisons(m_Colliders, delta);


    }


}

void PhysicSystem::clearColliders() {
    m_Colliders.clear();
}

void PhysicSystem::addCollider(Collider *collider) {
    m_Colliders.push_back(collider);
}

void PhysicSystem::clearRigidBodies()
{
    m_rigidBodies.clear();
}

void PhysicSystem::addRigidBody(RigidBody *body)
{
    m_rigidBodies.push_back(body);
}
