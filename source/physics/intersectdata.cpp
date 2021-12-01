#include "intersectdata.hpp"

IntersectData::IntersectData(const bool doesIntersect, const QVector3D direction) :
		m_isIntersect(doesIntersect),
		m_direction(direction)
{}

bool IntersectData::isIntersect() const {
	return m_isIntersect;
}

float IntersectData::getDistance() const {
	return m_direction.length();
}

QVector3D IntersectData::getDirection() const {
	return m_direction;
}
