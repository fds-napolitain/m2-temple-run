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

    inline const std::string getName() const {return m_name;}
    inline const Transform   getTransform() const {return m_transform;}
    inline std::vector<Component*> getComponents() const {return m_components;}


    template<typename T>
    inline void addComponent(T* component)
    {
        m_components.push_back(component);

    }
    void setParent(Entity* parent);
    void removeChild(Entity* child);

private:


    std::string m_name;
    Transform m_transform;
    Entity* m_parent;
    std::vector<Entity> m_children;
    std::vector<Component*> m_components;
};

#endif // ENTITY_H
