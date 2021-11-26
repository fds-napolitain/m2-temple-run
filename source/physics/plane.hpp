#ifndef PLANE_H
#define PLANE_H

#include <QVector3D>
#include "intersectdata.hpp"
#include "BoundingSphere.hpp"
#include "math.h"

class Plane
{
public:
    Plane(const QVector3D& normal, const float distance) :
    m_normal(normal),
    m_distance(distance)
    {};

    Plane normalize();
    IntersectData intersectSphere(const BoundingSphere& sphere);


    [[nodiscard]] inline QVector3D getNormal() const {return m_normal;}
    [[nodiscard]] inline float getDistance() const {return m_distance;}

private:
	const QVector3D m_normal;
    const float m_distance;
};

#endif // PLANE_H
