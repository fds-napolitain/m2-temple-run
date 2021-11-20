#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>
#include "component.hpp"

class Transform : public Component {
public:
    float scale = 1;
    QQuaternion rotate;
    QVector3D translate;
    QMatrix4x4 matrix;

    Transform();
    Transform(QQuaternion rotate, QVector3D translate = QVector3D(0.0, 0.0, 0.0), float s = 1);
    ~Transform() override;
    [[nodiscard]] QVector4D apply(QVector4D p) const;
    [[nodiscard]] QVector3D applyToPoint(QVector3D p) const;
    [[nodiscard]] QVector3D applyToVector(QVector3D v) const;
    [[nodiscard]] QVector3D applyToVersor(QVector3D v) const;
    Transform combineWith(Transform& transform);
    [[nodiscard]] Transform inverse() const;
    Transform interpolateWith(Transform& transform, float k) const;
	QMatrix4x4 getLocalMatrix();
};

#endif

