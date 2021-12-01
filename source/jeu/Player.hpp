//
// Created by Maxime Boucher on 01/12/2021.
//

#ifndef TEMPLERUN_PLAYER_HPP
#define TEMPLERUN_PLAYER_HPP

#include "source/transform.hpp"
#include "source/entity.hpp"
#include "source/physics/BoundingSphere.hpp"
#include "source/mesh.hpp"

class Player : public Entity {

private:

public:
	std::vector<Entity*> entities;
	Collider *collider;
	Player(std::string name);
	~Player() override;
	[[nodiscard]] std::vector<Entity*> getEntities() const;
	[[nodiscard]] Collider* getCollider() const;
	void updateTransforms(TimeStep deltaTime) override;

};


#endif //TEMPLERUN_PLAYER_HPP
