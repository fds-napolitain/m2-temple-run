//
// Created by edgar on 27/11/2021.
//

#ifndef TEMPLERUN_PHYSICSYSTEM_HPP
#define TEMPLERUN_PHYSICSYSTEM_HPP
#include "RigidBody.h"
#include "collider.hpp"
#include <vector>

class PhysicSystem {
public:
    PhysicSystem(){}


    void update(TimeStep delta);
    void clearRigidBodies();
    void clearColliders();
    void addRigidBody(RigidBody* body);
    void addCollider(Collider* collider);


protected:
    std::vector<RigidBody*> m_rigidBodies;
    std::vector<Collider*> m_Colliders;


};


#endif //TEMPLERUN_PHYSICSYSTEM_HPP
