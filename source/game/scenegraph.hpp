#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "source/engine/rendering/scene.hpp"
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
	Entity *mainDecor;

private:
    Player *player;
    Entity *m_root;

};

#endif // SCENEGRAPH_H
