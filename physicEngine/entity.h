#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>
#include "component.h"
#include "transform.h"

class Entity
{
public:
    Entity(const std::string& name) :
        m_name(name),
        m_transform(Transform())
    {}

    Entity(const std::string& name, const Transform& transform) :
        m_name(name),
        m_transform(transform)
    {}

private:
    template<typename T>
    inline void addComponent(T& component) { m_components.push_back(component); }

    const std::string m_name;
    const Transform m_transform;
    std::vector<Component> m_components;
};

#endif // ENTITY_H
