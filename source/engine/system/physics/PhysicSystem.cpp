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
                    entity->getTransform()->position.setX(15.0f);
                    if (entity->getName() == "obstacle") {
                        if (player->PointDeVie >= 0) {
                            player->PointDeVie -= 1;
                            player->justLostPDV=true;
							std::cout << " je perds une vie !\n";
                        }
                    }
                    if (entity->getName() == "meteorite") {
                        if (player->PointDeVie <= 3) {
                            player->PointDeVie += 1;
							std::cout << " je gagne une vie !\n";
                        }
                    }
					if (entity->getName() == "ring1" || entity->getName() == "ring2" || entity->getName() == "ring3" || entity->getName() == "ring4" || entity->getName() == "ring5" ||
							entity->getName() == "ring6" || entity->getName() == "ring7" || entity->getName() == "ring8" || entity->getName() == "ring9" || entity->getName() == "ring10") {
						player->score++;
						std::cout << " je gagne des points " << player->score << " !\n";
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

