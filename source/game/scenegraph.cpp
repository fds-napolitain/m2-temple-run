#include "scenegraph.hpp"
#include "source/engine/physics/aabb.hpp"

SceneGraph::SceneGraph(Entity *root) :
		Scene(),
		m_root(root)
{
    player = new Player("player");
	Transform* solTransform = new Transform(QQuaternion(), QVector3D(0, -4.0, 0), 1);
	Transform* rightTransform = new Transform(QQuaternion::fromAxisAndAngle(0.0, 0.0, 1.0, 90), QVector3D(7, -2.0, 0), 1);
	Transform* leftTransform = new Transform(QQuaternion::fromAxisAndAngle(0.0, 0.0, -1.0, 90), QVector3D(-7, -2.0, 0), 1);
	Transform* mainDecorTransform = new Transform(QQuaternion::fromAxisAndAngle(0.0, 0.0, 0.0,  0), QVector3D(0, 0.0, -100), 1);
	Transform* backgroundTransform = new Transform(QQuaternion::fromAxisAndAngle(1.0, 0.0, 0.0, 90), QVector3D(0, 0.0, -105), 1);
	Transform* obstacleTransform = new Transform(QQuaternion(), QVector3D(0,-1,0), 2);

	Entity* sol = new Entity("sol", solTransform);
	Entity* right = new Entity("right", rightTransform);
	Entity* left = new Entity("left", leftTransform);
	mainDecor = new Entity("mainDecor", mainDecorTransform);
	Light* obstacle = new Light("obstacle", obstacleTransform, QVector3D());
	Entity* background = new Entity("fond", backgroundTransform);

	Mesh* solMesh = new Mesh(GL_TRIANGLE_STRIP);
	solMesh->loadTexture(":/neige.png");

	Mesh* rightMesh = new Mesh(GL_TRIANGLE_STRIP);
	rightMesh->loadTexture(":/rock.png", QOpenGLTexture::LinearMipMapLinear);

	Mesh* leftMesh = new Mesh(GL_TRIANGLE_STRIP, QVector3D(1.0,0,0));

    Mesh* backgroundMesh = new Mesh(GL_TRIANGLE_STRIP);

    Mesh* obstacleMesh = new Mesh(GL_TRIANGLE_STRIP);
    obstacleMesh->setType(Mesh::Type::LIGHT);
    obstacleMesh->initCubeGeometry();
	obstacleMesh->loadTexture(":/grass.png");

	solMesh->initPlaneGeometry(16,16,100,100);
	rightMesh->initPlaneGeometry(16,16,100,100);
	leftMesh->initPlaneGeometry(16,16,100,100);
	backgroundMesh->initPlaneGeometry(16, 16, 100, 100);
	backgroundMesh->loadTexture(":/grass.png");

	AABB* b = new AABB(QVector3D(-1,-1,-100), QVector3D(1,1,-100));

	m_physics->addCollider(player->getCollider());
	m_physics->addCollider(b);

    obstacle->addComponent(b);
	sol->addComponent(solMesh);
	right->addComponent(rightMesh);
	left->addComponent(leftMesh);
	obstacle->addComponent(obstacleMesh);
	background->addComponent(backgroundMesh);

	addEntity(m_root, mainDecor);
	addEntity(mainDecor, obstacle);
	addEntity(mainDecor, sol);
	addEntity(mainDecor, right);
	addEntity(mainDecor, left);
	addEntity(m_root, player);
	addEntity(player, player->getEntities()[0]);
	addEntity(player, player->getEntities()[1]);
	addEntity(player, player->getEntities()[2]);
	addEntity(m_root, background);
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

	if (transform->position.z() >= 50) {
		transform->position = QVector3D(transform->position.x(), transform->position.y(), -100);
	}

	mainDecor->setTransform(transform);

//   updatePhysics(); <-- fait tout dans le scenegraph
     m_physics->update(deltaTime, m_drawnEntities, player );
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
