#include <iostream>
#include "entity.hpp"
#include "source/engine/physics/collider.hpp"

/**
 *
 * @param name
 */
Entity::Entity(std::string name) :
		m_name(std::move(name)),
		m_transform(new Transform()),
		m_parent(nullptr)
{}

/**
 *
 * @param name
 * @param transform
 */
Entity::Entity(std::string name, Transform *transform) :
		m_name(std::move(name)),
		m_transform(transform),
		m_parent(nullptr)
{}

/**
 *
 * @param name
 * @param transform
 * @param animation
 */
Entity::Entity(std::string name, Transform *transform, Transform *animation) :
m_name(std::move(name)),
m_transform(transform),
m_animation(animation),
m_parent(nullptr)
{}

/**
 *
 */
Entity::~Entity() {
	delete m_transform;
}

/**
 *
 * @param entity
 */
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

/**
 *
 * @param child
 */
void Entity::removeChild(Entity* child){
    for(unsigned int i =0; i<this->m_children.size(); i++){
        if(m_children[i] == child){
            m_children.erase(m_children.begin()+i);
        }
    }
}

/**
 * Applique la transform liée à la position.
 * @param transform
 */
void Entity::setTransform(Transform* transform)
{
    m_transform = transform;
}

/**
 *
 * @param component
 */
void Entity::addComponent(Component *component) {
	m_components.push_back(component);
}

/**
 *
 * @return
 */
std::string Entity::getName() const {
	return m_name;
}

/**
 *
 * @return
 */
const Entity *Entity::getParent() const {
	return m_parent;
}

/**
 *
 * @return
 */
std::vector<Component*> Entity::getComponents() const {
	return m_components;
}

/**
 * Retourne la transform liée à la position.
 * @return
 */
Transform *Entity::getTransform() const {
	return m_transform;
}

/**
 * Retourne l'ensemble des entités enfants
 * @return
 */
std::vector<Entity *> Entity::getChildren() const {
	return m_children;
}

/**
 * Ca c'est pour les animations
 * @param deltaTime
 */
void Entity::updateTransforms(TimeStep deltaTime) {
	// animations
	if (m_animation != nullptr) {
		m_transform->combineWith(m_animation->combineWith(deltaTime));
	}
	// collisions
    for(auto component : this->m_components){
        Collider* collider = dynamic_cast<Collider*>(component);
        if(collider != nullptr){
            collider->transformCollider( *m_transform);
        }
    }
}

/**
 * Retourne la transform liée à l'animation
 * @return
 */
Transform *Entity::getAnimation() const {
	return m_animation;
}

/**
 * Set la transform d'animation
 * @param animation
 */
void Entity::setAnimation(Transform* animation) {
	m_animation = animation;
}


