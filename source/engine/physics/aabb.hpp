#ifndef AABB_H
#define AABB_H

#include <QVector3D>
#include "intersectdata.hpp"
#include "algorithm"
#include "collider.hpp"

#include "source/engine/transform.hpp"



class AABB : public Collider {

public:
    AABB(int type, const QVector3D &mincorner, const QVector3D &maxcorner);
    IntersectData intersectAABB(const AABB& other);
    [[nodiscard]] QVector3D getMinCorner() const;
    [[nodiscard]] QVector3D getMaxCorner() const;
    void transformCollider(const Transform &transform) override;

private:
    QVector3D m_minCorner;
    QVector3D m_maxCorner;

};

#endif // AABB_H
