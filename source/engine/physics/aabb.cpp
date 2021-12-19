#include <cmath>
#include <iostream>
#include "aabb.hpp"


AABB::AABB(const QVector3D &mincorner, const QVector3D &maxcorner) :
        Collider(Collider::TYPE_AABB),
		m_minCorner(mincorner),
		m_maxCorner(maxcorner)
{}

QVector3D AABB::getMinCorner() const {return m_minCorner;}

QVector3D AABB::getMaxCorner() const {return m_maxCorner;}

IntersectData AABB::IntersectAABB(const AABB& other){
    QVector3D distances1 = other.getMinCorner() - m_maxCorner;
    QVector3D distances2 = m_minCorner - other.getMaxCorner();
    QVector3D distances = Transform::VecMax(distances1, distances2);

    float maxDistance = Transform::VecMaxValue(distances);

    return IntersectData(maxDistance < 0, distances);
}


void AABB::transformCollider(const Transform &transform) {
    Transform t = transform;
    if(oldPosition.isNull()){
        oldPosition = t.getWorldTranslate();
    }
    QVector3D velocity (t.getWorldTranslate() - oldPosition);
    oldPosition = t.getWorldTranslate();

    m_minCorner += velocity;
    m_maxCorner += velocity;
}

//IntersectData AABB::intersectBoundingSphere(const BoundingSphere &other) {
//    QVector3D aabbMax = this->getMaxCorner();
//    QVector3D aabbMin = this->getMinCorner();
//    //find closest point of the sphere on the aabb (clamping)
//    QVector3D closestPoint =
//            {
//                    std::fmax(aabbMin[0], std::fmin(other.getCenter()[0], aabbMax[0])),
//                    std::fmax(aabbMin[1], std::fmin(other.getCenter()[1], aabbMax[1])),
//                    std::fmax(aabbMin[2], std::fmin(other.getCenter()[2], aabbMax[2]))
//            };
//    QVector3D direction = (other.getCenter() - closestPoint);
//    float distanceSq = direction.lengthSquared();
//    float radiusSq = other.getRadius() * other.getRadius();
//
//    return IntersectData( distanceSq < radiusSq, direction.normalized());
//
//}
