#ifndef COLLIDER_H
#define COLLIDER_H

#include <QVector3D>
#include "ReferenceCounter.hpp"
#include "intersectdata.hpp"
#include "../transform.hpp"



class Collider : public ReferenceCounter
{
public:
    enum
    {
         TYPE_SPHERE,
         TYPE_AABB,
         TYPE_PLANE,

         TYPE_SIZE
    };
    explicit Collider(int type):
        ReferenceCounter(),
        m_type(type)
    {};

    [[nodiscard]] inline int getType() const {return m_type;}

    [[nodiscard]] IntersectData Intersect(const Collider& other) const;
    virtual void TransformCollider(const Transform& transform){};
    [[nodiscard]] inline virtual QVector3D getCenter() const {return QVector3D();}


    float Mass = 0.0;
    float Friction = 0.5f;
    float Restitution = 0.0f;
    float RestistuionMax = 0.5f; // prevent jittering


private:
    int m_type;
};

#endif // COLLIDER_H
