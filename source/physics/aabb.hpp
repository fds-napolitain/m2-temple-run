#ifndef AABB_H
#define AABB_H

#include <QVector3D>
#include "intersectdata.hpp"
#include "algorithm"
#include "../transform.hpp"


class AABB
{
public:
    AABB(const QVector3D& mincorner, const QVector3D& maxcorner) :
     m_minCorner(mincorner),
     m_maxCorner(maxcorner)
    {};

    IntersectData IntersectAABB(const AABB& other);

    [[nodiscard]] inline QVector3D getMinCorner() const {return m_minCorner;}
    [[nodiscard]] inline QVector3D getMaxCorner() const {return m_maxCorner;}

private:
    const QVector3D m_minCorner;
    const QVector3D m_maxCorner;
};

#endif // AABB_H