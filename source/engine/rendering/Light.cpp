//
// Created by edgar on 21/12/2021.
//

#include "Light.hpp"

/**
 *
 * @param name
 * @param transform
 * @param color
 */
Light::Light(std::string name, Transform *transform, QVector4D color) :
    Entity((std::string&)name, transform),
    m_color(color)
    {}

/**
 *
 * @return
 */
const QVector4D &Light::getColor() const {
    return m_color;
}
