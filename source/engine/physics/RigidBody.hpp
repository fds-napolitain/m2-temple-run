//
// Created by edgar on 27/11/2021.
//

#ifndef TEMPLERUN_RIGIDBODY_HPP
#define TEMPLERUN_RIGIDBODY_HPP
#include "source/engine/rendering/TimeStep.hpp"
#include "source/engine/rendering/component.hpp"
#include "intersectdata.hpp"
#include "collider.hpp"
#include <iostream>
#include <vector>

class RigidBody : public Component {

public:
    explicit RigidBody(Collider* collider);
    ~RigidBody() override;
    virtual void update(TimeStep delta);
    virtual  void applyForces();
    virtual void handleCollisons(std::vector<Collider*>& colliders,TimeStep delta);;
    enum class BodyType {
		STATIC = 0,
		DYNAMIC
	};
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
