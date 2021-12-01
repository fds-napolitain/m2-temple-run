#include "scenegraph.hpp"
#include <QTime>


SceneGraph::SceneGraph(Entity *root) :
		Scene(),
		m_root(root)
{
	Transform* soleilTransform = new Transform(QQuaternion(), QVector3D(0,1,0), 1);
	Transform* solT = new Transform(QQuaternion(), QVector3D(0,-2.0,0), 1);
	Transform *luneTransform = new Transform(QQuaternion(), QVector3D(2,0,0), 0.5);
	Transform* terreTransform = new Transform(QQuaternion(), QVector3D(2,0,0), 1);

	Entity* soleil = new Entity("soleil", soleilTransform );
	Entity* terre = new Entity("Terre", terreTransform);
	Entity* lune = new Entity("lune", luneTransform);
	Entity* sol = new Entity("Sol", solT);

	Mesh* solMesh = new Mesh(GL_TRIANGLE_STRIP);
	solMesh->initPlaneGeometry(8,8,5,5);

	Mesh* sphere = new Mesh(":/sphere.off", Mesh::OFFIO, GL_TRIANGLES);
//
	BoundingSphere* a = new BoundingSphere(soleilTransform->position, soleilTransform->scale);
	BoundingSphere* b = new BoundingSphere(solT->position, solT->scale);
	RigidBody* rb = new RigidBody(a);
	m_physics->addRigidBody(rb);

	m_physics->addCollider(a);
	m_physics->addCollider(b);
	soleil->addComponent(rb);
	sol->addComponent(solMesh);
	soleil->addComponent(sphere);
	terre->addComponent(sphere);
	lune->addComponent(sphere);

	addEntity(m_root, sol);
	addEntity(m_root, soleil);
	addEntity(soleil, terre);
	addEntity(terre, lune);
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

    if(current->getParent() != nullptr)
    {
        Transform* parentTransform = current->getParent()->getTransform();
        curTransform->matrix = (parentTransform->matrix * curTransform->getLocalModelMatrix());
    }
    else
    {

        curTransform->matrix = curTransform->getLocalModelMatrix();
    }

    QQuaternion a = QQuaternion::fromAxisAndAngle(QVector3D(0,1,0), 5 * deltaTime);
    //curTransform.rotate *= a;
    //Transform meteorTransform = meteor->getTransform();
   // meteorTransform.position += QVector3D(0,-0.5,0) * deltaTime;
    //meteor->setTransform(meteorTransform);
//    curTransform.matrix *= deltaTime;


    current->setTransform(curTransform);


    for(Entity * child : current->getChildren())
    {
        updateTransforms(child, deltaTime);
    }
}

Entity *SceneGraph::getRoot() {return m_root; }
