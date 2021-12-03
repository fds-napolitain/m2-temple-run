#include "collider.hpp"
#include "BoundingSphere.hpp"
#include "aabb.hpp"
#include <iostream>

IntersectData Collider::intersect(const Collider& other) const
{
    if(this->getType() == TYPE_SPHERE && other.getType() == TYPE_SPHERE )
    {
        BoundingSphere *self = (BoundingSphere*)this;
        return self->intersectBoundingSphere((BoundingSphere &) other);
    }

    if(this->getType() == TYPE_SPHERE && other.getType() == TYPE_AABB )
    {
        BoundingSphere *self = (BoundingSphere*)this;
        return self->intersectAABB((AABB &) other);
    }

    std::cout << "error";
    exit(1);
    return IntersectData(false, QVector3D());
}

Collider::Collider(int type) :
		ReferenceCounter(),
		m_type(type)
{}

int Collider::getType() const {
	return m_type;
}

void Collider::transformCollider(const Transform &transform) {

}

QVector3D Collider::getCenter() const {
	return QVector3D();
}


