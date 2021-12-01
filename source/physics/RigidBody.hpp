//
// Created by edgar on 27/11/2021.
//

#ifndef TEMPLERUN_RIGIDBODY_HPP
#define TEMPLERUN_RIGIDBODY_HPP
#include "../TimeStep.hpp"
#include "../component.hpp"
#include "intersectdata.hpp"
#include "collider.hpp"
#include <iostream>
#include <vector>

class RigidBody : public Component {
public:
    RigidBody(Collider* collider) : m_Collider(collider){};
    virtual ~RigidBody(){ delete m_Collider;}
    virtual void update(TimeStep delta)
    {
        QVector3D oldPos = m_transform.position;
        QVector3D acceleration = forces * (1.0f / mass);
        QVector3D oldVelocity = m_transform.velocity;
        m_transform.velocity +=  acceleration * delta;
        m_transform.position +=  ( oldVelocity + m_transform.velocity) * 0.5f  * delta;
        m_Collider->TransformCollider(m_transform);
        entityTransform->position =  m_transform.position;
        std::cout << m_transform.velocity[0] << "," << m_transform.velocity[1] << "," << m_transform.velocity[2] <<std::endl;

    };
    virtual  void applyForces(){
        forces = mass * gravity;
    };


    virtual void handleCollisons(std::vector<Collider*>& colliders,TimeStep delta)
    {
        for(auto* collider : colliders) {
            if(collider != m_Collider) {
                IntersectData intersect = m_Collider->Intersect(*collider);
                if (intersect.isIntersect()) {

                    QVector3D direction = intersect.getDirection().normalized();
                    QVector3D velocity1 = this->m_transform.velocity;

                    QVector3D reflection = velocity1 - (direction * (QVector3D::dotProduct(velocity1, direction) * 2));
                    this->m_transform.velocity = reflection;
                    m_Collider->TransformCollider(m_transform);


                }
            }
        }

    };
    enum class BodyType { STATIC = 0, DYNAMIC};
    BodyType m_type = BodyType::STATIC;
    Transform m_transform;
    Transform* entityTransform;
    QVector3D gravity = QVector3D(0.0, -2.82, 0.0);
    QVector3D forces  = QVector3D();
//    QVector3D acceleration  = QVector3D();
    Collider* m_Collider;
    float mass = 0.7;
    float bounce;





};


#endif //TEMPLERUN_RIGIDBODY_HPP
