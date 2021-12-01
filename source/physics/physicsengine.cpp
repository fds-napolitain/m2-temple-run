#include "physicsengine.hpp"
#include "stdio.h"

// ##################################################" CLASS WILL BE DELETED

PhysicsEngine::PhysicsEngine()
{

}


void PhysicsEngine::addObject(const PhysicObject& object)
{
    m_objects.push_back(object);
}

void PhysicsEngine::updateCollider(Transform& transform, int index)
{
    m_objects[index].integrate(transform);
}

void PhysicsEngine::handleCollisions(){
    for(unsigned int i=0; i<m_objects.size(); i++){
        for(unsigned int j=i+1; j<m_objects.size(); j++){

            IntersectData intersect = m_objects[i].getCollider().Intersect(m_objects[j].getCollider());
            if(intersect.isIntersect()){

                QVector3D direction = intersect.getDirection().normalized();
                QVector3D velocity1 = m_objects[i].getVelocity();
                //QVector3D velocity2 = m_objects[j].getVelocity();
                QVector3D reflection = velocity1 - (direction * (QVector3D::dotProduct(velocity1, direction) * 2));
                m_objects[i].setVelocity(reflection);
                m_objects[j].setVelocity(reflection * -1);
            }
        }
    }
}
