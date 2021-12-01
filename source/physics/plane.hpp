#ifndef PLANE_H
#define PLANE_H

#include <QVector3D>
#include "intersectdata.hpp"
#include "BoundingSphere.hpp"
#include "math.h"

class Plane {
public:
    Plane(const QVector3D& normal, float distance);;

    Plane normalize();
    IntersectData intersectSphere(const BoundingSphere& sphere);


    [[nodiscard]] QVector3D getNormal() const;
    [[nodiscard]] float getDistance() const;

private:
	const QVector3D m_normal;
    const float m_distance;
};

#endif // PLANE_H
