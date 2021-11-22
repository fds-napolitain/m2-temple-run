#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "scene.h"
#include "entity.h"

class SceneGraph : public Scene
{
public:
    SceneGraph(const Entity *root) :
        Scene(),
        m_root(root)
    {}

    ~SceneGraph()
    {
        delete m_root;
    }

    inline const Entity* getRoot() const {return m_root; }

private:
    const Entity *m_root;
};

#endif // SCENEGRAPH_H
