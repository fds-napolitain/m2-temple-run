#include "aabb.hpp"


AABB::AABB(int type, const QVector3D &mincorner, const QVector3D &maxcorner) :
		Collider(type), m_minCorner(mincorner), m_maxCorner(maxcorner)
{

}

QVector3D AABB::getMinCorner() const {return m_minCorner;}

QVector3D AABB::getMaxCorner() const {return m_maxCorner;}

IntersectData AABB::intersectAABB(const AABB& other) {
    QVector3D distances1 = other.getMinCorner() - m_maxCorner;
    QVector3D distances2 = m_minCorner - other.getMaxCorner();
    QVector3D distances = Transform::VecMax(distances1, distances2);

    float maxDistance = Transform::VecMaxValue(distances);

    return IntersectData(maxDistance < 0, distances);
}
