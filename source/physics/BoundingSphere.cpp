#include "BoundingSphere.hpp"

IntersectData BoundingSphere::instersectBoundingSphere(const BoundingSphere& other){
    float radiusDistance = m_radius + other.getRadius();

    QVector3D direction = (other.getCenter()- m_center);
    float centerDistance = direction.length();
    direction /= centerDistance ; // normalize direction

    float distance = centerDistance - radiusDistance;
    return IntersectData(centerDistance < radiusDistance, direction * distance );
}


void BoundingSphere::TransformCollider(const Transform& transform){
    // peut etre faire plus générale avec transform.applyToPoint(m_center) et m_radius = transform.scale ;
    m_center = transform.position; //m
};
