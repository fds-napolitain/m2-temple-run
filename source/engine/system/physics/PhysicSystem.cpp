//
// Created by edgar on 27/11/2021.
//

#include "PhysicSystem.hpp"


/**
 * Update les colliders, test les collision, traite les collision.
 * @param delta DeltraTime
 * @param entities liste d'entit�s
 * @param Player Le joueur
 */
void PhysicSystem::update(TimeStep delta, const std::vector<Entity*>& entities, Player* player) {
    for (auto entity : entities) {
        for (auto component : entity->getComponents()) {
            Collider* collider = dynamic_cast<Collider*>(component);
            if (collider != nullptr){
                collider->transformCollider(*entity->getTransform());
                IntersectData isIntersectingPlayer = player->collider->intersect(*collider);
                if (isIntersectingPlayer.isIntersect()) {
                    entity->getTransform()->position.setX(30.0f);
                    if (entity->getName() == "obstacle") {
                        if (player->PointDeVie >= 0) {
                            player->PointDeVie -= 1;
                            player->justLostPDV=true;
                        }
                    }
                    if (entity->getName() == "meteorite") {
                        if (player->PointDeVie <= 3) {
                            player->PointDeVie += 1;
                        }
                    }
					if (entity->getTag() == "ring") {
						player->score++;
					}
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

