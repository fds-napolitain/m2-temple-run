//
// Created by edgar on 27/11/2021.
//

#include "PhysicSystem.hpp"



void PhysicSystem::update(TimeStep delta, std::vector<Entity*> entities, Player* player)
{
    for(auto entity : entities)
    {
        for(auto component : entity->getComponents())
        {
            Collider* collider = dynamic_cast<Collider*>(component);

            if(collider != nullptr){
                collider->transformCollider(*entity->getTransform());
                IntersectData isIntersectingPlayer = player->collider->intersect(*collider);


                if(isIntersectingPlayer.isIntersect()){
                    entity->getTransform()->position.setX(15.0f); //? un truc marche pas.
                    std::cout << " je collide ! " << isIntersectingPlayer.getDirection().x() << " " << isIntersectingPlayer.getDirection().y() << " " << isIntersectingPlayer.getDirection().z() << " " << " \n";
                }
            }
        }
    }

}

void PhysicSystem::clearColliders() {
    m_Colliders.clear();
}

void PhysicSystem::addCollider(Collider *collider) {
    m_Colliders.push_back(collider);
}

