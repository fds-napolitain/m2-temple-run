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
        m_entities.emplace_back(root);
    }

    ~SceneGraph()
    {
        delete m_root;
    }

    inline Entity* getRoot()  {return m_root; }

private:
    Entity *m_root;
};

#endif // SCENEGRAPH_H
