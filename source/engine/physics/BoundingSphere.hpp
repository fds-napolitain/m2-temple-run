#ifndef BOUNDINGSPHERE_H
#define BOUNDINGSPHERE_H

#include <QVector3D>
#include "intersectdata.hpp"
#include "source/engine/components/physics/collider.hpp"
#include "aabb.hpp"


class BoundingSphere : public Collider {

public:
    BoundingSphere(const QVector3D& center, float radius);
    IntersectData intersectBoundingSphere(const BoundingSphere& other);
    IntersectData intersectAABB(const AABB& other);
    void transformCollider(const Transform& transform) override;
    [[nodiscard]] QVector3D getCenter() const override;
    [[nodiscard]] float getRadius() const;
private:
    QVector3D m_center;
    float m_radius;

};

#endif // BOUNDINGSPHERE_H
