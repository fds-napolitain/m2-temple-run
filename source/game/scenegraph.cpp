#include "scenegraph.hpp"

SceneGraph::SceneGraph(Entity *root) :
		Scene(),
		m_root(root)
{
	Player* player = new Player("player");
	Transform* solTransform = new Transform(QQuaternion(), QVector3D(0, -4.0, 0), 1);
	Transform* rightTransform = new Transform(QQuaternion::fromAxisAndAngle(0.0, 0.0, 1.0, 90), QVector3D(7, -2.0, 0), 1);
	Transform* leftTransform = new Transform(QQuaternion::fromAxisAndAngle(0.0, 0.0, -1.0, 90), QVector3D(-7, -2.0, 0), 1);
	Transform* mainDecorTransform = new Transform(QQuaternion::fromAxisAndAngle(0.0, 0.0, 0.0,  0), QVector3D(0, 0.0, -100), 1);

	Entity* sol = new Entity("sol", solTransform);
	Entity* right = new Entity("right", rightTransform);
	Entity* left = new Entity("left", leftTransform);
	mainDecor = new Entity("mainDecor", mainDecorTransform);
	Entity* sphere = new Entity("test");

	Mesh* solMesh = new Mesh(GL_TRIANGLE_STRIP);
	solMesh->loadTexture(":/neige.png");
	Mesh* rightMesh = new Mesh(GL_TRIANGLE_STRIP);
	rightMesh->loadTexture(":/rock.png");
	Mesh* leftMesh = new Mesh(GL_TRIANGLE_STRIP);
	Mesh* sphereMesh = new Mesh(":/sphere.off", Mesh::OFFIO, GL_TRIANGLES);
	solMesh->initPlaneGeometry(16,16,100,100);
	rightMesh->initPlaneGeometry(16,16,100,100);
	leftMesh->initPlaneGeometry(16,16,100,100);

	BoundingSphere* b = new BoundingSphere(solTransform->position, solTransform->scale);

	//m_physics->addCollider(player->getCollider());
	m_physics->addCollider(b);
	sol->addComponent(solMesh);
	right->addComponent(rightMesh);
	left->addComponent(leftMesh);
	sphere->addComponent(sphereMesh);

	addEntity(m_root, sol);
	addEntity(m_root, right);
	addEntity(m_root, left);
	addEntity(m_root, mainDecor);
	addEntity(mainDecor, sphere);
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
	Transform* transform = mainDecor->getTransform();
	transform->position += QVector3D(0.0, 0.0, 8.0*deltaTime);
	mainDecor->setTransform(transform);

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

	current->updateTransforms(deltaTime);

	for(Entity * child : current->getChildren()) {
        updateTransforms(child, deltaTime);
    }
}

Entity *SceneGraph::getRoot() {return m_root; }
