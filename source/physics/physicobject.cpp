#include "physicobject.hpp"

void PhysicObject::intergrate(float delta){
    m_position += m_velocity * delta;
}

PhysicObject::PhysicObject(const PhysicObject& other) :
    m_position(other.m_position),
    m_oldPosition(other.m_oldPosition),
    m_velocity(other.m_velocity),
    m_collider(other.m_collider)

{
	m_collider->addReference();
}

PhysicObject::~PhysicObject(){
   if(m_collider->removeReference()){
        delete m_collider;
   }

}
