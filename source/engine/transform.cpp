#include <iostream>
#include "transform.hpp"

/**
 * Constructeur par défaut
 */
Transform::Transform() {
    matrix = QMatrix4x4();
    rotate = QQuaternion();
    scale = 1;
    position = QVector3D();
}

/**
 * Constructeur par parametres
 * @param r
 * @param trans
 * @param s
 */
Transform::Transform(QQuaternion r, QVector3D trans, float s)
    :
        scale(s),
        rotate(r),
        position(trans),
        velocity(QVector3D()),
        rotation(QQuaternion()),
        rescale(1)

{

}

/**
 *
 * @return
 */
QMatrix4x4 Transform::getLocalModelMatrix() const {
    QMatrix4x4 modelMatrix = QMatrix4x4(rotate.toRotationMatrix() * scale);
    modelMatrix(0,3) = position.x();
    modelMatrix(1,3) = position.y();
    modelMatrix(2,3) = position.z();
    modelMatrix(3,3) = 1;
    return modelMatrix;
}

/**
 *
 * @param p
 * @return
 */
QVector3D Transform::applyToPoint(QVector3D p) const {
    return ( rotate.rotatedVector(p) * scale) + position   ;
}

/**
 *
 * @param v
 * @return
 */
QVector3D Transform::applyToVector(QVector3D v) const {
    return ( rotate.rotatedVector(v) * scale );
}

/**
 *
 * @param v
 * @return
 */
QVector3D Transform::applyToVersor(QVector3D v) const {
    return ( rotate.rotatedVector(v) );
}

/**
 *
 * @param p
 * @return
 */
QVector4D Transform::apply(QVector4D p) const {
    QVector3D t = QVector3D(p.x(), p.y(), p.z());
    t = (rotate.rotatedVector(t) + position )* scale;
    return QVector4D(t.x(), t.y(), t.z(), p.w());
}

/**
 * Combine deux transforms ensemble in-place et renvoit également l'objet (pour chainer les appels).
 * @param transform
 * @return
 */
Transform Transform::combineWith(Transform& transform) {
    this->rotate *= transform.rotate;
    this->position += transform.position;
    this->scale *= transform.scale;
    return *this;
}

/**
 *
 * @return
 */
QMatrix4x4 Transform::inverseWorld() const{
    return matrix.inverted();

}

/**
 *
 * @return
 */
QVector3D Transform::getWorldTranslate(){
    return QVector3D(this->matrix(0,3), this->matrix(1,3), this->matrix(2,3));


}

/**
 *
 * @param v1
 * @param v2
 * @return
 */
QVector3D Transform::vecMax(const QVector3D &v1, const QVector3D &v2) {
	QVector3D res;
	for (unsigned int i =0; i<3 ; i++ ) {
		res[i] = v1[i] > v2[i] ? v1[i] : v2[i];
	}
	return res;
}

/**
 *
 * @param v
 * @return
 */
float Transform::vecMaxValue(const QVector3D &v) {
	float res = v[0];
	for (unsigned int i =1; i<3 ; i++ ) {
		if(v[i] > res){
			res = v[i];
		}
	}
	return res;
}

/**
 *
 * @param v
 */
void Transform::printV3D(const QVector3D &v) {
    std::cout << "(" << v.x() << ", " << v.y() << ", "<< v.z() <<" )\n";
}

/**
 * Surcharge d'opérateur multiplier
 * @param local
 * @return
 */
Transform Transform::operator*(Transform &local) const {
	Transform res = Transform(this->rotate * local.rotate, this->position + local.position, this->scale * local.scale);
	return res;
}

/**
 *
 * @param t
 * @param k
 * @return
 */
Transform Transform::interpolate(Transform &t, float k) {
	Transform result;
	result.scale = this->scale * k +t.scale *(1-k);                 // scale interpolation
	QQuaternion::slerp(this->rotate, t.rotate, k);                        // spherical linear interpolation for quaternion
	result.position = this->position * k+t.position * (1-k);     // translation interpolation
	return result;
}

/**
 *
 * @param m
 */
void Transform::printMatrix4x4(const QMatrix4x4 &m) {
    std::cout << " ( " << m(0,0) << " " << m(0,1) << " " << m(0,2) << " "  << m(0,3) << " ) " <<  "\n"
              << " ( " << m(1,0) << " " << m(1,1) << " " << m(1,2) << " "  << m(1,3) << " ) " <<  "\n"
              << " ( " << m(2,0) << " " << m(2,1) << " " << m(2,2) << " "  << m(2,3) << " ) " <<  "\n"
              << " ( " << m(3,0) << " " << m(3,1) << " " << m(3,2) << " "  << m(3,3) << " ) " <<  "\n";
}

