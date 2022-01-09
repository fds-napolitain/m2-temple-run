#include <cmath>
#include "BoundingSphere.hpp"

BoundingSphere::BoundingSphere(const QVector3D &center, float radius) :
		Collider(Collider::TYPE_SPHERE),
		m_center(center),
		m_radius(radius)
{}

IntersectData BoundingSphere::intersectBoundingSphere(const BoundingSphere& other){
    float radiusDistance = m_radius + other.getRadius();

    QVector3D direction = (other.getCenter()- m_center);
    float centerDistance = direction.length();
    direction /= centerDistance ; // normalize direction

    float distance = centerDistance - radiusDistance;
    return IntersectData(centerDistance < radiusDistance, direction * distance );
}


void BoundingSphere::transformCollider(const Transform& transform){
    // peut etre faire plus générale avec transform.applyToPoint(m_center) et m_radius = transform.scale ;
    Transform t = transform;
    m_center = t.getWorldTranslate(); //m
}

QVector3D BoundingSphere::getCenter() const {
	return m_center;
}

float BoundingSphere::getRadius() const {
	return m_radius;
}

IntersectData BoundingSphere::intersectAABB(const AABB &other) {
    QVector3D aabbMax = other.getMaxCorner();
    QVector3D aabbMin = other.getMinCorner();
    //find closest point of the sphere on the aabb (clamping)
    QVector3D closestPoint =
            {
                std::fmax(aabbMin[0], std::fmin(m_center[0], aabbMax[0])),
                std::fmax(aabbMin[1], std::fmin(m_center[1], aabbMax[1])),
                std::fmax(aabbMin[2], std::fmin(m_center[2], aabbMax[2]))
            };
    QVector3D direction = (m_center - closestPoint);
    float distanceSq = direction.lengthSquared();
    float radiusSq = m_radius * m_radius;

    return IntersectData( distanceSq < radiusSq, direction.normalized());
}
