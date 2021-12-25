//
// Created by Maxime Boucher on 01/12/2021.
//

#include "Player.hpp"

#include <utility>

Player::Player(std::string name) : Entity(std::move(name)) {
	this->setTransform(new Transform(QQuaternion(), QVector3D(0, -3, 0), 1));
	Transform* playerBaseTransform = new Transform(QQuaternion::fromAxisAndAngle(0.4, -0.2, 0.2, 14), QVector3D(0, 0, 0), 1);
	Transform* playerMidTransform = new Transform(QQuaternion::fromAxisAndAngle(0.1, 0.2, -0.2, 14), QVector3D(0, 1.3, 0), 0.8);
	Transform* playerTopTransform = new Transform(QQuaternion::fromAxisAndAngle(-0.2, 0.4, -0.2, 14), QVector3D(0, 2.3, 0), 0.6);

	Transform* playerBaseAnimation = new Transform(QQuaternion::fromAxisAndAngle(-1.0, 0.0, 0.0, 90), QVector3D(), 1);
	Transform* playerMidAnimation = new Transform(QQuaternion::fromAxisAndAngle(1.0, 0.0, 0.0, 90), QVector3D(), 1);
	Transform* playerTopAnimation = new Transform(QQuaternion::fromAxisAndAngle(-1.0, 0.0, 0.0, 45), QVector3D(), 1);

	Entity* playerBase = new Entity("playerBase", playerBaseTransform, playerBaseAnimation);
	entities.push_back(playerBase);

	Entity* playerMid = new Entity("playerMid", playerMidTransform, playerMidAnimation);
	entities.push_back(playerMid);

	Entity* playerTop = new Entity("playerTop", playerTopTransform, playerTopAnimation);
	entities.push_back(playerTop);

	collider = new BoundingSphere(playerBaseTransform->position, playerBaseTransform->scale);

	Mesh* sphere = new Mesh(":/sphere.off", Mesh::OFFIO, GL_TRIANGLES);
	sphere->loadTexture(":/neige.png");

//    playerBase->addComponent(collider);
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
