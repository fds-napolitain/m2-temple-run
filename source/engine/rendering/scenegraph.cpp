#include "scenegraph.hpp"
#include "source/engine/physics/aabb.hpp"

/**
 * Constructeur par défaut
 */
SceneGraph::SceneGraph() {
	m_root = new Entity("World");
}

/**
 *
 * @param root
 */
SceneGraph::SceneGraph(Entity *root) :
		Scene(),
		m_root(root)
{
}

/**
 *
 */
SceneGraph::~SceneGraph() {
	delete m_root;
}

/**
 *
 * @param parent
 * @param entity
 */
void SceneGraph::addEntity(Entity *parent, Entity *entity)
{
    entity->setParent(parent);
    m_drawnEntities.emplace_back(entity);
}

/**
 *
 * @param deltaTime
 */
void SceneGraph::update(TimeStep deltaTime)
{

    updateTransforms(m_root, deltaTime);/*
	Transform* transform = mainDecor->getTransform();
	transform->position += QVector3D(0.0, 0.0, 8.0*deltaTime);

	if (transform->position.z() >= 50) {
		transform->position = QVector3D(transform->position.x(), transform->position.y(), -100);
	}

//	mainDecor->setTransform(transform);

//   updatePhysics(); <-- fait tout dans le scenegraph
     m_physics->update(deltaTime, m_drawnEntities, player );*/
}

/**
 *
 * @param current
 * @param deltaTime
 */
void SceneGraph::updateTransforms(Entity* current, TimeStep deltaTime)
{
    Transform* curTransform = current->getTransform();

    if (current->getParent() != nullptr) {
        Transform* parentTransform = current->getParent()->getTransform();
        curTransform->matrix = (parentTransform->matrix * curTransform->getLocalModelMatrix());
    } else {

        curTransform->matrix = curTransform->getLocalModelMatrix();
    }

	current->updateTransforms(deltaTime);

	for(Entity * child : current->getChildren()) {
        updateTransforms(child, deltaTime);
    }
}

/**
 *
 * @return
 */
Entity *SceneGraph::getRoot() {
	return m_root;
}
