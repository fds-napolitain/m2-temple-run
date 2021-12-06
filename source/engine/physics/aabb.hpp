#ifndef AABB_H
#define AABB_H

#include <QVector3D>
#include "intersectdata.hpp"
#include "algorithm"
#include "source/engine/transform.hpp"
#include "collider.hpp"


class AABB : public Collider {

public:
    AABB(int type, const QVector3D &mincorner, const QVector3D &maxcorner);
    IntersectData intersectAABB(const AABB& other);
    [[nodiscard]] QVector3D getMinCorner() const;
    [[nodiscard]] QVector3D getMaxCorner() const;

private:
    const QVector3D m_minCorner;
    const QVector3D m_maxCorner;

};

#endif // AABB_H
