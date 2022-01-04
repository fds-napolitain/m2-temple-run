//
// Created by edgar on 27/11/2021.
//

#ifndef TEMPLERUN_PHYSICSYSTEM_HPP
#define TEMPLERUN_PHYSICSYSTEM_HPP
#include "collider.hpp"
#include "../TimeStep.hpp"
#include "source/engine/rendering/entity.hpp"
#include "source/game/Player.hpp"
#include <vector>
#include <iostream>

class PhysicSystem {

public:
    PhysicSystem() = default;
	void update(TimeStep delta, const std::vector<Entity*>& entities, Player* player);
    void clearRigidBodies();
    void clearColliders();
    void addCollider(Collider* collider);

protected:
    std::vector<Collider*> m_Colliders ;


};


#endif //TEMPLERUN_PHYSICSYSTEM_HPP
