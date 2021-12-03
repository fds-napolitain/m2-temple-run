//
// Created by Maxime Boucher on 01/12/2021.
//

#include "Player.hpp"

#include <utility>

Player::Player(std::string name) : Entity(std::move(name)) {
	this->setTransform(new Transform(QQuaternion(), QVector3D(0, 0, 0), 1));
	Transform* playerBaseTransform = new Transform(QQuaternion(), QVector3D(0, 0, 0), 1);
	Transform* playerMidTransform = new Transform(QQuaternion(), QVector3D(0, 1.3, 0), 0.8);
	Transform* playerTopTransform = new Transform(QQuaternion(), QVector3D(0, 2.6, 0), 0.6);

	Entity* playerBase = new Entity("playerBase", playerBaseTransform);
	entities.push_back(playerBase);

	Entity* playerMid = new Entity("playerMid", playerMidTransform);
	entities.push_back(playerMid);

	Entity* playerTop = new Entity("playerTop", playerTopTransform);
	entities.push_back(playerTop);

	collider = new BoundingSphere(playerBaseTransform->position, playerBaseTransform->scale);

	Mesh* sphere = new Mesh(":/sphere.off", Mesh::OFFIO, GL_TRIANGLES);

	playerBase->addComponent(sphere);
	playerMid->addComponent(sphere);
	playerTop->addComponent(sphere);
}

std::vector<Entity*> Player::getEntities() const {
	return entities;
}

Collider *Player::getCollider() const {
	return collider;
}

Player::~Player() {
	for (const auto &entity: entities) {
		delete entity;
	}
	delete collider;
}

void Player::updateTransforms(TimeStep deltaTime) {
	Transform* animationBase = entities[0]->getTransform();
	Transform* animationMid = entities[1]->getTransform();
	animationBase->rotate *= QQuaternion::fromAxisAndAngle(1.0, 0.0, 0.0, 90 * deltaTime);
	animationMid->rotate *= QQuaternion::fromAxisAndAngle(-1.0, 0.0, 0.0, 90 * deltaTime);
	entities[0]->setTransform(animationBase);
	entities[1]->setTransform(animationMid);
}
