#include "entity.h"

void Entity::setParent(Entity* entity){
    //si parent existe déja == changement de parent donc delete l'ancien child
    if(m_parent != nullptr){
        m_parent->removeChild(entity);
    }

    if(entity != nullptr){
        m_parent = entity;
        m_parent->m_children.emplace_back(*this);
    }
}

void Entity::removeChild(Entity* child){
    for(unsigned int i =0; i<this->m_children.size(); i++){
        Entity* m_child = &m_children[i];
        if(m_child == child){
            m_children.erase(m_children.begin()+i);
        }
    }
}

