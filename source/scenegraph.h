#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "scene.h"
#include "entity.h"

class SceneGraph : public Scene
{
public:
    SceneGraph(Entity *root) :
        Scene(),
        m_root(root)
    {
        Mesh* sphere = new Mesh(":/sphere.off", Mesh::OFFIO);

        Entity* soleil = new Entity("soleil", Transform(QQuaternion(), QVector3D(), 1));
        Entity* terre = new Entity("Terre", Transform(QQuaternion(), QVector3D(2,0,0), 1));

        soleil->addComponent(sphere);
        terre->addComponent(sphere);


        addEntity(m_root, soleil);
        addEntity(soleil, terre);
        //m_entities.emplace_back(root);
    }

    ~SceneGraph()
    {
        delete m_root;
    }

    virtual void update();
    inline Entity* getRoot()  {return m_root; }
    void addEntity(Entity* parent, Entity* entity);
    void updateTransforms(Entity* root_node);

private:

    Entity *m_root;
};

#endif // SCENEGRAPH_H
