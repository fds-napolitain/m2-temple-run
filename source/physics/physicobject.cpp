#include "physicobject.hpp"


// ##################################################" CLASS WILL BE DELETED

void PhysicObject::integrate(Transform& transform){
   // m_transform.combineWith(transform);
    m_collider->TransformCollider(m_transform);
    
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
