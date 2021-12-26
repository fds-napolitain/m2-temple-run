#ifndef COLLIDER_H
#define COLLIDER_H

#include <QVector3D>
#include "source/engine/physics/ReferenceCounter.hpp"
#include "source/engine/physics/intersectdata.hpp"
#include "source/engine/transform.hpp"
#include "source/engine/components/component.hpp"


class Collider : public Component {

private:
	int m_type;

public:
    enum
    {
         TYPE_SPHERE,
         TYPE_AABB,
         TYPE_PLANE,
         TYPE_SIZE,
    };
    explicit Collider(int type);
    [[nodiscard]] int getType() const;
    [[nodiscard]] IntersectData intersect(const Collider& other) const;
    virtual void transformCollider(const Transform& transform);
    [[nodiscard]] virtual QVector3D getCenter() const;


    float mass = 0.0;
    float friction = 0.5f;
    float restitution = 0.0f;
    float restitutionMax = 0.5f; // prevent jittering
    QVector3D oldPosition;
	int getType() override;

};

#endif // COLLIDER_H
