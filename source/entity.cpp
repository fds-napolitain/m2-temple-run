#include "entity.hpp"

Entity::Entity(std::string name) :
		m_name(std::move(name)),
		m_transform(new Transform()),
		m_parent(nullptr)
{}

Entity::Entity(std::string name, Transform *transform) :
		m_name(std::move(name)),
		m_transform(transform),
		m_parent(nullptr)
{}

Entity::~Entity() {
	delete m_transform;
	for(Entity* child : m_children){
		delete child;
	}
	for(Component* component : m_components){
		delete component;
	}
}

void Entity::setParent(Entity* entity){
    //si parent existe déja == changement de parent donc delete l'ancien child
    if(m_parent != nullptr){
        m_parent->removeChild(entity);
    }

    if(entity != nullptr){
        m_parent = entity;
        m_parent->m_children.emplace_back(this);
    }
}

void Entity::removeChild(Entity* child){
    for(unsigned int i =0; i<this->m_children.size(); i++){
        if(m_children[i] == child){
            m_children.erase(m_children.begin()+i);
        }
    }
}

void Entity::setTransform(Transform* transform)
{
    m_transform = transform;
}

void Entity::addComponent(Component *component) {
	m_components.push_back(component);
	RigidBody* rb = dynamic_cast<RigidBody*>(component);
	if(rb != nullptr){
		rb->m_transform = *m_transform;
		rb->entityTransform = m_transform;
	}

}

std::string Entity::getName() const {
	return m_name;
}

const Entity *Entity::getParent() const {
	return m_parent;
}

std::vector<Component *> Entity::getComponents() const {
	return m_components;
}

Transform *Entity::getTransform() const {
	return m_transform;
}

std::vector<Entity *> Entity::getChildren() const {
	return m_children;
}

void Entity::updateTransforms(TimeStep deltaTime) {

}


