#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "source/scene.hpp"
#include "Player.hpp"
#include <QTime>


class SceneGraph : public Scene
{
public:
    SceneGraph(Entity *root);
    ~SceneGraph() override;
    void update(TimeStep timeStep) override;
    Entity* getRoot();
    void addEntity(Entity* parent, Entity* entity);
    void updateTransforms(Entity* root_node, TimeStep deltaTime);

private:
    Entity *m_root;
	Entity *mainDecor;

};

#endif // SCENEGRAPH_H
