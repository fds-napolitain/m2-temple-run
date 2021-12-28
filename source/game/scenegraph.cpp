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
	Transform* obstacleTransform = new Transform(QQuaternion(), QVector3D(-5,-1,0), 2);
	Transform* obstacleTransform2 = new Transform(QQuaternion(), QVector3D(0,-1,0), 2);

	Entity* sol = new Entity("sol", solTransform);
	Entity* right = new Entity("right", rightTransform);
	Entity* left = new Entity("left", leftTransform);
	mainDecor = new Entity("mainDecor", mainDecorTransform);
	Light* obstacle = new Light("obstacle", obstacleTransform, QVector4D(1.0,1.0,1.0,1.0));
	Light* obstacle2 = new Light("obstacle", obstacleTransform, QVector4D(1.0,1.0,1.0,1.0));
	Entity* background = new Entity("fond", backgroundTransform);

	Mesh* solMesh = new Mesh(GL_TRIANGLE_STRIP);
	solMesh->loadTexture(":/neige.png");

	Mesh* rightMesh = new Mesh(GL_TRIANGLE_STRIP);
	rightMesh->loadTexture(":/rock.png", QOpenGLTexture::LinearMipMapLinear);

	Mesh* leftMesh = new Mesh(GL_TRIANGLE_STRIP, QVector3D(1.0,0,0));

    Mesh* backgroundMesh = new Mesh(GL_TRIANGLE_STRIP);

    Mesh* obstacleMesh = new Mesh(GL_TRIANGLE_STRIP);
    Mesh* obstacleMesh2 = new Mesh(GL_TRIANGLE_STRIP);
    obstacleMesh->setType(Mesh::Type::LIGHT);
    obstacleMesh2->setType(Mesh::Type::LIGHT);
    obstacleMesh->initCubeGeometry();
    obstacleMesh2->initCubeGeometry();
	obstacleMesh->loadTexture(":/grass.png");
	obstacleMesh2->loadTexture(":/grass.png");

	solMesh->initPlaneGeometry(16,16,100,100);
	rightMesh->initPlaneGeometry(16,16,100,100);
	leftMesh->initPlaneGeometry(16,16,100,100);
	backgroundMesh->initPlaneGeometry(16, 16, 100, 100);
	backgroundMesh->loadTexture(":/grass.png");

	AABB* b = new AABB(QVector3D(-1,-1,-100), QVector3D(1,1,-100));

	m_physics->addCollider(player->getCollider());
	m_physics->addCollider(b);

    obstacle->addComponent(b);
    obstacle2->addComponent(b);
	sol->addComponent(solMesh);
	right->addComponent(rightMesh);
	left->addComponent(leftMesh);
	obstacle->addComponent(obstacleMesh);
	obstacle2->addComponent(obstacleMesh2);
	background->addComponent(backgroundMesh);

	addEntity(m_root, mainDecor);
	addEntity(mainDecor, obstacle);
	addEntity(mainDecor, obstacle2);
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
	// On fait  ce qui concerne le joueur

	

	// on regarde sur quel rail est le joueur s'il n'est pas entrain de bouger.
	if (!isMovingRight && !isMovingLeft)
	{
		if (transform->position.x() < 4.0f && transform->position.x()> -4.0f)
			{
				joueur_rl = false;
				joueur_rm = true;
				joueur_rr = false;		
			}
			if (transform->position.x() >= 4.0f)
			{
				joueur_rl = true;
				joueur_rm = false;
				joueur_rr = false;
			}
			if (transform->position.x() <= -4.0f) {
				joueur_rl = false;
				joueur_rm = false;
				joueur_rr = true;
			}

			
			if (joueur_rl) transform->position.setX(distanceWhenMoving);
			if (joueur_rm) transform->position.setX(0.0f);
			if (joueur_rr) transform->position.setX(-distanceWhenMoving);

			
	}

	
	
	// on déplace le joueur selon son rail et son mouvement
	float deplacement = (distanceWhenMoving / timeWhenMoving)*deltaTime;

	
	if (isMovingLeft && !isMovingRight)
	{
		distMoved += deplacement;
		std::cout << "moving left";
		transform->position += QVector3D(deplacement, 0.0, 0.0);
		
		player->isMovingLeft = true;
		player->isMovingRight = false;
		

	}	
	if (isMovingRight && !isMovingLeft)
	{
		distMoved += deplacement;
		std::cout << "moving right";
		transform->position += QVector3D(-deplacement, 0.0, 0.0);

		player->isMovingLeft = false;
		player->isMovingRight = true;

	}

	

	if (distMoved >= distanceWhenMoving)
	{
		isMovingLeft = false;
		isMovingRight = false;

		player->isMovingLeft = false;
		player->isMovingRight = false;
		distMoved = 0.0f;
	}

	//On fait le saut:

	if (isJumping)
	{
		if (transform->position.y() > -tailleJump)
		{
			transform->position += QVector3D(0.0f, (-tailleJump / tempsJump) * deltaTime, 0.0f);
		}
		else
		{
			transform->position.setY(-tailleJump);
			isJumping = false;
			player->isJumping = false;
			hasJumped = true;
			player->hasJumped = true;
		}
	}
	if (hasJumped)
	{
		if (transform->position.y() < 0.0f)
		{
			transform->position += QVector3D(0.0f, (tailleJump / tempsJump) * deltaTime, 0.0f);
		}
		else
		{
			transform->position.setY(0.0f);
			isJumping = false;
			player->isJumping = false;
			hasJumped = false;
			player->hasJumped = false;
		}
	}



	//On fait le scrolling:
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
