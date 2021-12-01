#include "physicobject.hpp"


// ##################################################" CLASS WILL BE DELETED

PhysicObject::PhysicObject(Collider *collider, const Transform &transform) :
		m_transform(transform),
		m_oldPosition(collider->getCenter()),
		m_collider(collider)
{}

void PhysicObject::integrate(Transform& transform){
   // m_transform.combineWith(transform);
	m_collider->transformCollider(m_transform);
    
}

PhysicObject::PhysicObject(const PhysicObject& other) :
    m_transform(other.m_transform),
    m_oldPosition(other.m_oldPosition),
    m_collider(other.m_collider)

{
	m_collider->addReference();
}

PhysicObject::~PhysicObject(){
   if(m_collider->removeReference()){
        delete m_collider;
   }

}

const Collider &PhysicObject::getCollider() {
	Transform translation = Transform();
	translation.position = m_transform.position - m_oldPosition;
	m_oldPosition = m_transform.position;
	m_collider->transformCollider(translation);

	return *m_collider;
}

void PhysicObject::setVelocity(QVector3D vel) {
	m_transform.velocity = vel;
}

QVector3D PhysicObject::getPosition() const { return m_transform.position;}

QVector3D PhysicObject::getVelocity() const { return m_transform.velocity;}
