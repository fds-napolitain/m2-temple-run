#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <QVector3D>

class Transform
{
public:
    Transform();

    inline static QVector3D VecMax(const QVector3D& v1,const QVector3D& v2 ){
        QVector3D res;
        for (unsigned int i =0; i<3 ; i++ ) {
            res[i] = v1[i] > v2[i] ? v1[i] : v2[i];
        }return res;
    }

    inline static float VecMaxValue(const QVector3D& v){
        float res = v[0];
        for (unsigned int i =1; i<3 ; i++ ) {
            if(v[i] > res){
                res = v[i];
            }
        }
        return res;
    }
};


#endif // TRANSFORM_H
