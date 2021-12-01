#ifndef PHYSICOBJECT_H
#define PHYSICOBJECT_H

#include "BoundingSphere.hpp"
#include "source/engine/rendering/transform.hpp"
#include <QVector3D>
#include "source/engine/rendering/TimeStep.hpp"
#include "source/engine/rendering/component.hpp"


// ##################################################" CLASS WILL BE DELETED

class PhysicObject : public Component {

public:
    PhysicObject(Collider* collider,  const Transform& transform);;
    PhysicObject(const PhysicObject& other);
    ~PhysicObject() override;
    void integrate(Transform& transform);
    [[nodiscard]] QVector3D getPosition() const;
    [[nodiscard]] QVector3D getVelocity() const;
	const Collider& getCollider();
	void setVelocity(QVector3D vel);

private:
    Transform m_transform;
    QVector3D m_oldPosition;
    Collider* m_collider;

};

#endif // PHYSICOBJECT_H
