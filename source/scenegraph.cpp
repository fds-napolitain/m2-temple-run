#include "scenegraph.hpp"
#include <QTime>


void SceneGraph::addEntity(Entity *parent, Entity *entity)
{
    entity->setParent(parent);
    m_drawnEntities.emplace_back(entity);
}


void SceneGraph::update(TimeStep deltaTime)
{

    updateTransforms(m_root, deltaTime);
    //updateCollisons();
}

void SceneGraph::updateTransforms(Entity* current, TimeStep deltaTime)
{
    Transform curTransform = current->getTransform();

    if(current->getParent() != nullptr)
    {
        Transform parentTransform = current->getParent()->getTransform();
        curTransform.matrix = (parentTransform.matrix * curTransform.getLocalModelMatrix());
    }
    else
    {

        curTransform.matrix = curTransform.getLocalModelMatrix();
    }

    QQuaternion a = QQuaternion::fromAxisAndAngle(QVector3D(0,1,0), 5 * deltaTime);
    curTransform.rotate *= a;
//    curTransform.matrix *= deltaTime;


    current->setTransform(curTransform);


    for(Entity * child : current->getChildren())
    {
        updateTransforms(child, deltaTime);
    }
}
