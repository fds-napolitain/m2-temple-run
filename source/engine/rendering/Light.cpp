
#include "Light.hpp"

//
// Created by edgar on 21/12/2021.
//
Light::Light(std::string name, Transform *transform, QVector3D color) :
    Entity(name, transform),
    m_color(color)
    {}
