//
// Created by edgar on 21/12/2021.
//

#ifndef TEMPLERUN_LIGHT_HPP
#define TEMPLERUN_LIGHT_HPP


#include "entity.hpp"
#include <QVector4D>

class Light : public Entity{
public:
    Light(std::string name, Transform* transformation, QVector4D color);

    const QVector4D &getColor() const;

private:
    QVector4D m_color;

};


#endif //TEMPLERUN_LIGHT_HPP
