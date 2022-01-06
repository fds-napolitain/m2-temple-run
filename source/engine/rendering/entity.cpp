#include "entity.hpp"

/**
 * Constructeur par nom
 * @param name
 */
Entity::Entity(std::string name) :
		m_name(std::move(name)),
		m_transform(new Transform()),
		m_parent(nullptr)
{}

/**
 * Constructeur par nom, transform (position)
 * @param name
 * @param transform
 */
Entity::Entity(std::string name, Transform *transform) :
		m_name(std::move(name)),
		m_transform(transform),
		m_parent(nullptr)
{}

/**
 * Destructeur
 */
Entity::~Entity() {
	delete m_transform;
}

/**
 * Set le parent (entity) de this
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
 * Supprime un enfant entity attaché à this
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
 * Set la transform position de this
 * @param transform
 */
void Entity::setTransform(Transform* transform) {
    m_transform = transform;
}

/**
 * Rajoute un component à this
 * @param component
 */
void Entity::addComponent(Component *component) {
	m_components.push_back(component);
}

/**
 * Retourne le nom de this
 * @return
 */
std::string Entity::getName() const {
	return m_name;
}

/**
 * Retourne le parent de this
 * @return
 */
const Entity *Entity::getParent() const {
	return m_parent;
}

/**
 * Retourne les components de this
 * @return
 */
std::vector<Component *> Entity::getComponents() const {
	return m_components;
}

/**
 * Retourne la transform (position) de this
 * @return
 */
Transform *Entity::getTransform() const {
	return m_transform;
}

/**
 * Retourne les fils (entity) de this
 * @return
 */
std::vector<Entity *> Entity::getChildren() const {
	return m_children;
}

/**
 * Met à jour this selon ses components
 * @param deltaTime
 */
void Entity::updateTransforms(TimeStep deltaTime) {
    for (auto component : this->m_components) {
		int ctype = component->getCType();
		if (ctype == COLLIDER) {
			auto collider = dynamic_cast<Collider*>(component);
			collider->transformCollider(*m_transform);
		} else if (ctype == ANIMATION) {
			auto animation = dynamic_cast<Animation*>(component);
			m_transform->position += animation->transform.position * deltaTime;
			m_transform->rotate *= animation->transform.rotate * deltaTime;
			m_transform->scale = animation->transform.scale;
		} else {
			std::cout << "Component not recognized.\n";
		}
    }
}


