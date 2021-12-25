#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <QVector3D>
#include <QMatrix4x4>
#include "TimeStep.hpp"

class Transform {
public:
    Transform();
    Transform(QQuaternion rotate, QVector3D trans, float s = 1.0);

   //fields
    // world transform
    QMatrix4x4  matrix;
    //local transform
    //TODO: change float to vector3d to handle non uniform scales
    float       scale;
    QQuaternion rotate;
    QVector3D   position;
	QVector3D   velocity;
    QQuaternion rotation;
    float       rescale;

   //methods
    QMatrix4x4 getModelMatrix();
    [[nodiscard]] QMatrix4x4 getLocalModelMatrix() const;
    void computeModelMatrix();
    void computeModelMatrix(const QMatrix4x4 &parentMatrix);
    QVector3D getWorldTranslate();
    [[nodiscard]] QVector4D apply(QVector4D p) const;
    [[nodiscard]] QVector3D applyToPoint(QVector3D  p) const;
    [[nodiscard]] QVector3D applyToVector(QVector3D v) const;
    [[nodiscard]] QVector3D applyToVersor(QVector3D v) const;
    Transform combineWith(Transform t);
	[[nodiscard]] Transform combineWith(TimeStep deltaTime) const;
    [[nodiscard]] QMatrix4x4 inverseWorld() const;
    Transform interpolate(Transform &t, float k) const;
    Transform operator*(Transform& local) const;
	static QVector3D VecMax(const QVector3D& v1,const QVector3D& v2 );
	static float VecMaxValue(const QVector3D& v);
	static void printV3D(const QVector3D& v);
	static void printMatrix4x4(const QMatrix4x4& m);

};


#endif // TRANSFORM_H
