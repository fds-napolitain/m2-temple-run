#include "scenegraph.hpp"

void SceneGraph::addEntity(Entity *parent, Entity *entity)
{
    entity->setParent(parent);
    m_drawnEntities.emplace_back(entity);
}


void SceneGraph::update()
{
    updateTransforms(m_root);
    //updateCollisons();
}

void SceneGraph::updateTransforms(Entity* current)
{
    Transform curTransform = current->getTransform();
    if(current->getParent() != nullptr)
    {
        Transform parentTransform = current->getParent()->getTransform();
        curTransform.matrix = parentTransform.matrix * curTransform.getLocalModelMatrix();
    }
    else
    {
        curTransform.matrix = curTransform.getLocalModelMatrix();
    }
    QQuaternion a = QQuaternion::fromAxisAndAngle(QVector3D(0,1,0), 0.5);
    curTransform.rotate *= a;
    current->setTransform(curTransform);


    for(Entity * child : current->getChildren())
    {
        updateTransforms(child);
    }
}
