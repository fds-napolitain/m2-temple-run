//
// Created by Maxime Boucher on 01/12/2021.
//

#ifndef TEMPLERUN_PLAYER_HPP
#define TEMPLERUN_PLAYER_HPP

#include "source/engine/transform.hpp"
#include "source/engine/rendering/entity.hpp"
#include "source/engine/components/physics/collider/BoundingSphere.hpp"
#include "source/engine/components/rendering/mesh.hpp"

class Player : public Entity {

private:

public:
	std::vector<Entity*> entities;
	Collider *collider;
	Player(std::string name);
	~Player() override;
	[[nodiscard]] std::vector<Entity*> getEntities() const;
	[[nodiscard]] Collider* getCollider() const;

};


#endif //TEMPLERUN_PLAYER_HPP
