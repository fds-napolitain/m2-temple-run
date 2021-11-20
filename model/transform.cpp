#include "transform.hpp"

Transform::Transform() = default;

Transform::Transform(QQuaternion r, QVector3D t, float s) {
	translate = t;
	rotate = r;
	scale = s;
}

Transform::~Transform() = default;

QVector4D Transform::apply(QVector4D p) const {
    // verifier que this.scale est uniforme
    // verifie que this.matrix n'est pas une normal (matrice de transformation normal)
    QVector3D t = QVector3D(p.x(), p.y(), p.z());
    t = (rotate.rotatedVector(t) + translate) * scale;
    return QVector4D(t.x(), t.y(), t.z(), p.w());
}

QVector3D Transform::applyToPoint(QVector3D p) const {
    return (rotate.rotatedVector(p) + translate) * scale;
}

QVector3D Transform::applyToVector(QVector3D v) const {
    return (rotate.rotatedVector(v)) * scale;
}

QVector3D Transform::applyToVersor(QVector3D v) const {
    return rotate.rotatedVector(v);
}

QMatrix4x4 Transform::getLocalMatrix() {
	matrix = (QMatrix4x4(rotate.toRotationMatrix()) * scale);
	matrix(0, 3) = translate.x();
	matrix(1, 3) = translate.y();
	matrix(2, 3) = translate.z();
	matrix(3, 3) = 1;
	return matrix;
}

Transform Transform::combineWith(Transform& transform) {
	std::cout << scale * transform.scale << "\n";
	this->rotate *= transform.rotate;
	this->translate += transform.translate;
	this->scale *= transform.scale;
	return *this;
}

Transform Transform::inverse() const {
    return Transform(rotate.inverted(), -translate, 1/scale);
}

Transform Transform::interpolateWith(Transform& transform, float k) const {
    Transform t;
    t.scale = scale*k + transform.scale*(1-k);
    QQuaternion::slerp(rotate, transform.rotate, k);
    t.translate = translate*k + transform.translate*(1-k);
    return t;
}
