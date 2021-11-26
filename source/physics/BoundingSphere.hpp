#ifndef BOUNDINGSPHERE_H
#define BOUNDINGSPHERE_H

#include <QVector3D>
#include "intersectdata.hpp"
#include "collider.hpp"


class BoundingSphere : public Collider
{
public:
    BoundingSphere(const QVector3D& center, float radius) :
    Collider(Collider::TYPE_SPHERE),
    m_center(center),
    m_radius(radius)
    {};

    IntersectData instersectBoundingSphere(const BoundingSphere& other );
    void Transform(const QVector3D& translation) override;

    [[nodiscard]] inline QVector3D getCenter() const override { return m_center;}
    [[nodiscard]] inline float getRadius() const { return m_radius;}
private:
    QVector3D m_center;
    float m_radius;

};

#endif // BOUNDINGSPHERE_H
