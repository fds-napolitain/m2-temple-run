#include "scenegraph.hpp"

SceneGraph::SceneGraph(Entity *root) :
		Scene(),
		m_root(root)
{
	Player* player = new Player("player");
	Transform* solTransform = new Transform(QQuaternion(), QVector3D(0, -2.0, 0), 1);

	Entity* sol = new Entity("sol", solTransform);

	Mesh* solMesh = new Mesh(GL_TRIANGLE_STRIP);
	solMesh->initPlaneGeometry(8,8,5,5);

	BoundingSphere* b = new BoundingSphere(solTransform->position, solTransform->scale);

	//m_physics->addCollider(player->getCollider());
	m_physics->addCollider(b);
	sol->addComponent(solMesh);

	addEntity(m_root, sol);
	addEntity(m_root, player);
	addEntity(player, player->getEntities()[0]);
	addEntity(player, player->getEntities()[1]);
	addEntity(player, player->getEntities()[2]);
}

SceneGraph::~SceneGraph() {
	delete m_root;
}

void SceneGraph::addEntity(Entity *parent, Entity *entity)
{
    entity->setParent(parent);
    m_drawnEntities.emplace_back(entity);
}


void SceneGraph::update(TimeStep deltaTime)
{

    updateTransforms(m_root, deltaTime);
//    updatePhysics();
     m_physics->update(deltaTime);
}

void SceneGraph::updateTransforms(Entity* current, TimeStep deltaTime)
{
    Transform* curTransform = current->getTransform();

    if (current->getParent() != nullptr) {
        Transform* parentTransform = current->getParent()->getTransform();
        curTransform->matrix = (parentTransform->matrix * curTransform->getLocalModelMatrix());
    } else {

        curTransform->matrix = curTransform->getLocalModelMatrix();
    }


	for(Entity * child : current->getChildren()) {
        updateTransforms(child, deltaTime);
    }
	current->updateTransforms(deltaTime);
}

Entity *SceneGraph::getRoot() {return m_root; }
