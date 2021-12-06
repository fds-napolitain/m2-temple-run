//
// Created by edgar on 27/11/2021.
//

#include "RigidBody.hpp"

RigidBody::RigidBody(Collider *collider) : m_Collider(collider){}

RigidBody::~RigidBody() { delete m_Collider;}

void RigidBody::update(TimeStep delta) {
	QVector3D oldPos = m_transform.position;
	QVector3D acceleration = forces * (1.0f / mass);
	QVector3D oldVelocity = m_transform.velocity;
	m_transform.velocity +=  acceleration * delta;
	m_transform.position +=  ( oldVelocity + m_transform.velocity) * 0.5f  * delta;
	m_Collider->transformCollider(m_transform);
	entityTransform->position =  m_transform.position;
	//std::cout << m_transform.velocity[0] << "," << m_transform.velocity[1] << "," << m_transform.velocity[2] <<std::endl;

}

void RigidBody::applyForces() {
    if(m_type != BodyType::STATIC)
    {
        forces = mass * gravity;
    }
    else
    {
        forces = QVector3D();
    }
}

void RigidBody::handleCollisions(std::vector<Collider *> &colliders, TimeStep delta) {
	for(auto* collider : colliders) {
		if(collider != m_Collider) {
			IntersectData intersect = m_Collider->intersect(*collider);
			if (intersect.isIntersect()) {

				QVector3D direction = intersect.getDirection().normalized();
				QVector3D velocity1 = this->m_transform.velocity;
				std::cout << "collision\n";

				QVector3D reflection = velocity1 - (direction * (QVector3D::dotProduct(velocity1, direction) * 2));
				this->m_transform.velocity = reflection;
				m_Collider->transformCollider(m_transform);
			}
		}
	}

}
