#ifndef INTERSECTDATA_H
#define INTERSECTDATA_H

#include <QVector3D>

class IntersectData {

public:
    IntersectData(bool doesIntersect, QVector3D direction);
    [[nodiscard]] bool isIntersect() const;
    [[nodiscard]] float getDistance() const;
    [[nodiscard]] QVector3D getDirection() const;

private:
    const bool m_isIntersect;
    const QVector3D m_direction;

};

#endif // INTERSECTDATA_H
