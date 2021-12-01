#include "plane.hpp"

Plane::Plane(const QVector3D &normal, const float distance) :
		m_normal(normal),
		m_distance(distance)
{};

Plane Plane::normalize(){
    float magnitude = m_normal.length();
    return Plane(m_normal / magnitude,m_distance/magnitude);
}

IntersectData Plane::intersectSphere(const BoundingSphere& sphere){

    float distFromSphereCenter = fabs(QVector3D::dotProduct(sphere.getCenter(), m_normal) + m_distance);
    float distanceFromSphere = distFromSphereCenter - sphere.getRadius();
    return IntersectData(distanceFromSphere < 0 , m_normal * distanceFromSphere);
}

QVector3D Plane::getNormal() const {
	return m_normal;
}

float Plane::getDistance() const {
	return m_distance;
}
