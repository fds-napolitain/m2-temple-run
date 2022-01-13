//
// Created by edgar on 21/12/2021.
//

#include "Light.hpp"

/**
 * Crée une entité de type lumière (avec nom transform et couleur).
 * @param name
 * @param transform
 * @param color
 */
Light::Light(std::string name, Transform *transform, QVector4D color) :
    Entity((std::string&)name, transform),
    m_color(color)
    {}

/**
 * Retourne la couleur
 * @return
 */
const QVector4D &Light::getColor() const {
    return m_color;
}

int Light::getEType()
{
    return LIGHT;
}
