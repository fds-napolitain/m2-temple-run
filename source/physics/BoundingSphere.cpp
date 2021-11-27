#include "BoundingSphere.hpp"

IntersectData BoundingSphere::intersectBoundingSphere(const BoundingSphere& other){
    float radiusDistance = m_radius + other.getRadius();

    QVector3D direction = (other.getCenter()- m_center);
    float centerDistance = direction.length();
    direction /= centerDistance; // normalize direction

    float distance = centerDistance - radiusDistance;
    return IntersectData(centerDistance < radiusDistance, direction * distance );
}


void BoundingSphere::Transform(const QVector3D& transform){
    m_center += transform;
};
