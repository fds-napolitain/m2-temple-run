#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "scene.hpp"
#include "entity.hpp"


class SceneGraph : public Scene
{
public:
    explicit SceneGraph(Entity *root);
    ~SceneGraph() override;
    void update(TimeStep timeStep) override;
    inline Entity* getRoot();
    void addEntity(Entity* parent, Entity* entity);
    void updateTransforms(Entity* root_node, TimeStep deltaTime);

private:
    Entity *m_root;

};

#endif // SCENEGRAPH_H
