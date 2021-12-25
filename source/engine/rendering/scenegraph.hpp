#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "source/engine/rendering/scene.hpp"
#include "source/game/prefabs/Player.hpp"
#include <QTime>


class SceneGraph : public Scene
{
public:
	// METHODS
	SceneGraph();
    explicit SceneGraph(Entity *root);
    ~SceneGraph() override;
    void update(TimeStep timeStep) override;
    Entity* getRoot();
	void addEntity(Entity* parent, Entity* entity);
    void updateTransforms(Entity* root_node, TimeStep deltaTime);

	// SCENES
	void initMenu();
	void initGame();
	//Entity* mainDecor;

private:
	// ATTRIBUTES
    Entity *m_root;
	//Entity* player;

};

#endif // SCENEGRAPH_H
