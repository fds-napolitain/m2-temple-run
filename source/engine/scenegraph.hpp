#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "scene.hpp"
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
    Entity* getRoot();
	void addEntity(Entity* parent, Entity* entity);
	virtual void update(TimeStep timeStep, Entity* current = nullptr);
	virtual void keyPressEvent(QKeyEvent *event, TimeStep step) = 0;

};

#endif // SCENEGRAPH_H
