#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>
#include "component.hpp"
#include "transform.hpp"

class Entity
{
public:
    Entity(const std::string& name) :
        m_name(name),
        m_transform(Transform()),
        m_parent(nullptr)
    {}

    Entity(const std::string& name, const Transform& transform) :
        m_name(name),
        m_transform(transform),
        m_parent(nullptr)
    {}

    ~Entity()
    {

        delete m_parent;
        for(Entity* child : m_children){
            delete child;
        }
        for(Component* component : m_components){
            delete component;
        }
    }

    inline const std::string        getName() const {return m_name;}
    inline const Entity*            getParent() const {return m_parent;}

    inline std::vector<Component*>  getComponents() const {return m_components;}
    inline const Transform          getTransform() const {return m_transform;}
    inline std::vector<Entity*>     getChildren() const {return m_children;}


    template<typename T>
    inline void addComponent(T* component)
    {
        m_components.push_back(component);

    }
    void setParent(Entity* parent);
    void setTransform(Transform& transform);
    void removeChild(Entity* child);

private:


    std::string m_name;
    Transform m_transform;
    Entity* m_parent;
    std::vector<Entity*> m_children;
    std::vector<Component*> m_components;
};

#endif // ENTITY_H
