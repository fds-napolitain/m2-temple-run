#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <utility>
#include <vector>
#include "component.hpp"
#include "transform.hpp"

class Entity
{
public:
    explicit Entity(std::string  name) :
        m_name(std::move(name)),
        m_transform(Transform()),
        m_parent(nullptr)
    {}

    Entity(std::string  name, const Transform& transform) :
        m_name(std::move(name)),
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

    [[nodiscard]] inline const std::string getName() const {return m_name;}
    [[nodiscard]] inline const Entity* getParent() const {return m_parent;}

    [[nodiscard]] inline std::vector<Component*> getComponents() const {return m_components;}
    [[nodiscard]] inline const Transform getTransform() const {return m_transform;}
    [[nodiscard]] inline std::vector<Entity*> getChildren() const {return m_children;}


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
