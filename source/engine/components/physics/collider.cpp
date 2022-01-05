#include "collider.hpp"
#include "source/engine/components/physics/collider/BoundingSphere.hpp"
#include "source/engine/components/physics/collider/aabb.hpp"
#include <iostream>

/**
 *
 * @param type
 */
Collider::Collider(int type) :
		ReferenceCounter(),
		m_type(type)
{}

/**
 *
 * @param other
 * @return
 */
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

//    if(this->getType() == TYPE_AABB && other.getType() == TYPE_SPHERE   ){
//        std::cout << "AABB AVEC SPHERE\n";
//        AABB *self = (AABB*)this;
//        return self->intersectBoundingSphere((BoundingSphere &) other);
//    }

    std::cout << "error";
    exit(1);
    return IntersectData(false, QVector3D());
}

/**
 *
 * @return
 */
int Collider::getType() const {
	return m_type;
}

/**
 *
 * @param transform
 */
void Collider::transformCollider(const Transform &transform)
{
}

/**
 *
 * @return
 */
QVector3D Collider::getCenter() const {
	return QVector3D();
}

/**
 *
 * @return
 */
int Collider::getCType() {
	return COLLIDER;
}


