//
// Created by edgar on 27/11/2021.
//

#include "PhysicSystem.hpp"



void PhysicSystem::update(TimeStep delta, const std::vector<Entity*>& entities, Player* player) {
    for (auto entity : entities) {
        for (auto component : entity->getComponents()) {
            Collider* collider = dynamic_cast<Collider*>(component);
            if (collider != nullptr){
                collider->transformCollider(*entity->getTransform());
                IntersectData isIntersectingPlayer = player->collider->intersect(*collider);
                if (isIntersectingPlayer.isIntersect()) {
                    Transform* transformAfterCollision = entity->getTransform();
                    transformAfterCollision->position.setX(15.0);
                    entity->setTransform(transformAfterCollision);
                    if(player->lifes > 0){
                        int index = 3-player->lifes;
                        Transform* test = player->entities[index]->getTransform();
                        test->position.setX(-15.0);
                        player->entities[index]->setTransform(test);
                        player->lifes--;
                    }
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

