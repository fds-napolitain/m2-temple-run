//
// Created by edgar on 27/11/2021.
//

#ifndef TEMPLERUN_RIGIDBODY_H
#define TEMPLERUN_RIGIDBODY_H
#include "../TimeStep.hpp"
#include "collider.hpp"
#include <vector>

class RigidBody {
public:
    RigidBody();
    virtual ~RigidBody(){};
    virtual void update(TimeStep delta){};
    virtual  void applyForces(){};
    virtual void handleCollisons(std::vector<Collider*> colliders){};



};


#endif //TEMPLERUN_RIGIDBODY_H
