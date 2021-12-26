//
// Created by edgar on 21/12/2021.
//

#ifndef TEMPLERUN_LIGHT_HPP
#define TEMPLERUN_LIGHT_HPP


#include "entity.hpp"
#include <QVector4D>

class Light : public Entity {

private:
	QVector4D m_color;

public:
	Light(std::string name, Transform* transformation, QVector4D color);
	[[nodiscard]] const QVector4D &getColor() const;

};


#endif //TEMPLERUN_LIGHT_HPP
