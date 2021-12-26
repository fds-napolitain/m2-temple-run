#include "scenegraph.hpp"
#include "source/engine/components/physics/collider/aabb.hpp"

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
void SceneGraph::update(TimeStep deltaTime, Entity* current)
{
	if (current == nullptr) {
		update(deltaTime, m_root);
	} else {
		Transform* curTransform = current->getTransform();
		if (current->getParent() != nullptr) {
			Transform* parentTransform = current->getParent()->getTransform();
			curTransform->matrix = (parentTransform->matrix * curTransform->getLocalModelMatrix());
		} else {
			curTransform->matrix = curTransform->getLocalModelMatrix();
		}
		current->update(deltaTime);
		for(Entity* child : current->getChildren()) {
			update(deltaTime, child);
		}
	}
}

/**
 *
 * @return
 */
Entity *SceneGraph::getRoot() {
	return m_root;
}
