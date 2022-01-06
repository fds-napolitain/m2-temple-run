#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <utility>
#include <vector>
#include "source/engine/transform.hpp"
#include "source/engine/components/component.hpp"
#include "../TimeStep.hpp"
#include <iostream>
#include "source/engine/components/physics/collider.hpp"
#include "source/engine/components/rendering/Animation.hpp"

class Entity {

public:
    Entity(std::string name);
    Entity(std::string name, Transform* transform);
    virtual ~Entity();
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] const Entity* getParent() const;
    [[nodiscard]] std::vector<Component*> getComponents() const;
    [[nodiscard]] Transform* getTransform() const;
    [[nodiscard]] std::vector<Entity*> getChildren() const;
	void addComponent(Component* component);
    void setParent(Entity* parent);
    void setTransform(Transform* transform);
    void removeChild(Entity* child);
	virtual void updateTransforms(TimeStep deltaTime);
    

private:
    std::string m_name;
    Transform*  m_transform;
    Entity* m_parent;
    std::vector<Entity*> m_children;
    std::vector<Component*> m_components;
};

#endif // ENTITY_H
