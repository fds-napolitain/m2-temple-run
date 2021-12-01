#ifndef PHYSICOBJECT_H
#define PHYSICOBJECT_H

#include "BoundingSphere.hpp"
#include "../transform.hpp"
#include <QVector3D>
#include "../TimeStep.hpp"
#include "../component.hpp"


// ##################################################" CLASS WILL BE DELETED

class PhysicObject : public Component
{
public:
    PhysicObject(Collider* collider,  const Transform& transform) :
     m_transform(transform),
     m_oldPosition(collider->getCenter()),
     m_collider(collider)
    {};

    PhysicObject(const PhysicObject& other);
    virtual ~PhysicObject();


    void integrate(Transform& transform);

    [[nodiscard]] inline QVector3D getPosition() const { return m_transform.position;}
    [[nodiscard]] inline QVector3D getVelocity() const { return m_transform.velocity;}

    inline const Collider& getCollider() {
        Transform translation = Transform();
        translation.position = m_transform.position - m_oldPosition;
        m_oldPosition = m_transform.position;
        m_collider->TransformCollider(translation);

        return *m_collider;
    }
    inline void setVelocity(QVector3D vel){
        m_transform.velocity = vel;
    }
private:

    Transform m_transform;

    QVector3D m_oldPosition;
    Collider* m_collider;
};

#endif // PHYSICOBJECT_H
