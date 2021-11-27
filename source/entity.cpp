#include "entity.hpp"

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

void Entity::setTransform(Transform& transform)
{
    m_transform = transform;
}

