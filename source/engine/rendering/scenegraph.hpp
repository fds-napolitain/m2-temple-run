#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "source/engine/rendering/scene.hpp"
#include "source/game/prefabs/Player.hpp"
#include <QTime>
#include <QKeyEvent>


class SceneGraph : public Scene
{

protected:
	// ATTRIBUTES
	Entity *m_root;
public:
	// METHODS
	SceneGraph();
    explicit SceneGraph(Entity *root);
    ~SceneGraph() override;
    void update(TimeStep timeStep) override;
    Entity* getRoot();
	void addEntity(Entity* parent, Entity* entity);
    void updateTransforms(Entity* root_node, TimeStep deltaTime);
	virtual void keyPressEvent(QKeyEvent *event, TimeStep step) = 0;

};

#endif // SCENEGRAPH_H
