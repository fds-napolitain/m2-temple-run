#include "scenegraph.hpp"
#include "source/engine/physics/aabb.hpp"

SceneGraph::SceneGraph(Entity *root) :
		Scene(),
		m_root(root)
{
    player = new Player("player"); //ps: les static bougent, faut changer le nom
	Transform* solTransform = new Transform(QQuaternion(), QVector3D(0, -4.0, 0), 1);
	Transform* rightTransform = new Transform(QQuaternion::fromAxisAndAngle(0.0, 0.0, 1.0, 90), QVector3D(-8, -2.0, 0), 1);
	Transform* staticRightTransform = new Transform(QQuaternion::fromAxisAndAngle(0.0, 0.0, 1.0, 90), QVector3D(-8, -2.0, -100), 1);
	Transform* movingRightTransform = new Transform(QQuaternion::fromAxisAndAngle(0.0, 0.0, -1.0, 90), QVector3D(4, -2.0, -50), 1);
	Transform* leftTransform = new Transform(QQuaternion::fromAxisAndAngle(0.0, 0.0, -1.0, 90), QVector3D(-30, -2.0, 0), 1);
	Transform* staticLeftTransform = new Transform(QQuaternion::fromAxisAndAngle(0.0, 0.0, -1.0, 90), QVector3D(-30, -2.0, -100), 1);
	Transform* movingLeftTransform = new Transform(QQuaternion::fromAxisAndAngle(0.0, 0.0, -1.0, 90), QVector3D(-30, -2.0, -50), 1);
	Transform* mainDecorTransform = new Transform(QQuaternion::fromAxisAndAngle(0.0, 0.0, 0.0,  0), QVector3D(0, 0.0, -100), 1);
	Transform* backgroundTransform = new Transform(QQuaternion::fromAxisAndAngle(1.0, 0.0, 0.0, 90), QVector3D(-30, 0.0, -105), 1);
	Transform* soleilTransform = new Transform(QQuaternion::fromAxisAndAngle(1.0, 0.0, 0.0, 90), QVector3D(0.0, 100.0f, 20), 5);
	Transform* meteoriteTransform = new Transform(QQuaternion::fromAxisAndAngle(1.0, 0.0, 0.0, 90), QVector3D(0.0, 100.0f, -2.5*scrollingSpeed), 5);
	

	Entity* sol = new Entity("sol", solTransform);
	right = new Entity("right", rightTransform);
	staticRight = new Entity("staticright", staticRightTransform);
	movingRight = new Entity("right", staticRightTransform);
	left = new Entity("left", leftTransform);
	staticLeft = new Entity("staticleft", staticLeftTransform);
	movingLeft = new Entity("left", staticLeftTransform);
	mainDecor = new Entity("mainDecor", mainDecorTransform);
	background = new Entity("fond", backgroundTransform);
	meteorite = new Entity("meteorite", meteoriteTransform);
	soleil = new Light("soleil", soleilTransform, QVector4D(5.0, 5.0, 5.0, 1.0));


	Mesh* solMesh = new Mesh(GL_TRIANGLE_STRIP);
	solMesh->loadTexture(":/neige.png");

	Mesh* rightMesh = new Mesh(GL_TRIANGLE_STRIP);
	rightMesh->loadTextureHM(":/Heightmap_Rocky.png",":/grass.png",":/rock.png",":/neige.png");
	
	Mesh* staticRightMesh = new Mesh(GL_TRIANGLE_STRIP);
	staticRightMesh->loadTextureHM(":/Heightmap_Rocky.png",":/neige.png",":/rock.png",":/neige.png");

	Mesh* movingRightMesh = new Mesh(GL_TRIANGLE_STRIP);
	movingRightMesh->loadTextureHM(":/Heightmap_Rocky.png", ":/grass.png", ":/rock.png", ":/rock.png");

	Mesh* leftMesh = new Mesh(GL_TRIANGLE_STRIP);
	leftMesh->loadTextureHM(":/Heightmap_Mountain.png",":/grass.png",":/rock.png",":/neige.png");
	
	Mesh* staticLeftMesh = new Mesh(GL_TRIANGLE_STRIP);
	staticLeftMesh->loadTextureHM(":/Heightmap_Rocky.png",":/rock.png",":/rock.png",":/neige.png");

	Mesh* movingLeftMesh = new Mesh(GL_TRIANGLE_STRIP);
	movingLeftMesh->loadTextureHM(":/Heightmap_Mountain.png", ":/rock.png", ":/neige.png", ":/neige.png");

    Mesh* backgroundMesh = new Mesh(GL_TRIANGLE_STRIP);

	Mesh* soleilMesh = new Mesh(":/sphere.off", Mesh::OFFIO, GL_TRIANGLES);
	Mesh* meteoriteMesh = new Mesh(":/sphere.off", Mesh::OFFIO, GL_TRIANGLES);
	
	solMesh->initPlaneGeometry(16,16,200,200);
    solMesh->setAllNormals(QVector3D(0.0, 1.0,0.0));
	rightMesh->initPlaneGeometry(16,16,100,100);
	staticRightMesh->initPlaneGeometry(16,16,100,100);
	movingRightMesh->initPlaneGeometry(256,256,100,100);
	leftMesh->initPlaneGeometry(16,16,100,100);
	staticLeftMesh->initPlaneGeometry(16,16,100,100);
	movingLeftMesh->initPlaneGeometry(16,16,100,100);
	backgroundMesh->initPlaneGeometry(16, 16, 100, 100);
	backgroundMesh->loadTextureHM(":/ciel.png", ":/ciel.png", ":/ciel.png", ":/ciel.png");
	meteoriteMesh->loadTexture(":/neige.png");


	BoundingSphere* meteoriteBS = new BoundingSphere(QVector3D(0.0f, 0.0f, 0.0f), 5.0f);


	m_physics->addCollider(player->getCollider());
	m_physics->addCollider(meteoriteBS);

	sol->addComponent(solMesh);
	right->addComponent(rightMesh);
	staticRight->addComponent(staticRightMesh);
	movingRight->addComponent(movingRightMesh);
	left->addComponent(leftMesh);
	staticLeft->addComponent(staticLeftMesh);
	movingLeft->addComponent(movingLeftMesh);
	soleil->addComponent(soleilMesh);
	meteorite->addComponent(meteoriteMesh);

	background->addComponent(backgroundMesh);

	
	meteorite->addComponent(meteoriteBS);

	addEntity(m_root, mainDecor);
	addEntity(mainDecor, staticRight);
	addEntity(mainDecor, movingRight);
	addEntity(mainDecor, staticLeft);
	addEntity(mainDecor, movingLeft);
	addEntity(mainDecor, sol);
	addEntity(mainDecor, right);
	addEntity(mainDecor, left);
	addEntity(m_root, player);
	addEntity(player, player->getEntities()[0]);
	addEntity(player, player->getEntities()[1]);
	addEntity(player, player->getEntities()[2]);
	addEntity(m_root, background);
	addEntity(m_root, soleil);
	addEntity(mainDecor, meteorite);



	//Obstacles: faudrait faire un objet entiy obstacle avec tout �a un jour.

	//1:
	Transform* obstacle1Transform = new Transform(QQuaternion(), QVector3D(obstacle1X, -1, obstacle1Z), 0.2);
	obstacle1 = new Entity("obstacle", obstacle1Transform);
	Mesh* obstacle1Mesh = new Mesh("../models/Rock.obj", Mesh::OBJIO, GL_TRIANGLES);
	obstacle1Mesh->setType(Mesh::Type::LIGHT);
    //	obstacle1Mesh->initCubeGeometry();
	obstacle1Mesh->loadTexture(":/Rock_1_Emissive.jpg");
	AABB* obstacle1AABB = new AABB(QVector3D(-1 + obstacle1X, -1, obstacle1Z - 1), QVector3D(1 + obstacle1X, 1, obstacle1Z + 1));
	m_physics->addCollider(obstacle1AABB);
	obstacle1->addComponent(obstacle1AABB);
	obstacle1->addComponent(obstacle1Mesh);
	addEntity(mainDecor, obstacle1);


	//2:
	Transform* obstacle2Transform = new Transform(QQuaternion(), QVector3D(obstacle2X, -1, obstacle2Z), 2);
	obstacle2 = new Light("obstacle", obstacle2Transform, QVector4D(1.0, 1.0, 1.0, 1.0));
	Mesh* obstacle2Mesh = new Mesh(GL_TRIANGLE_STRIP);
	obstacle2Mesh->setType(Mesh::Type::LIGHT);
	obstacle2Mesh->initCubeGeometry();
	obstacle2Mesh->loadTexture(":/grass.png");
	AABB* obstacle2AABB = new AABB(QVector3D(-1 + obstacle2X, -1, obstacle2Z - 1), QVector3D(1 + obstacle2X, 1, obstacle2Z + 1));
	m_physics->addCollider(obstacle2AABB);
	obstacle2->addComponent(obstacle2AABB);
	obstacle2->addComponent(obstacle2Mesh);
	addEntity(mainDecor, obstacle2);

	//3:
	Transform* obstacle3Transform = new Transform(QQuaternion(), QVector3D(obstacle3X, -1, obstacle3Z), 2);
	obstacle3 = new Light("obstacle", obstacle3Transform, QVector4D(1.0, 1.0, 1.0, 1.0));
	Mesh* obstacle3Mesh = new Mesh(GL_TRIANGLE_STRIP);
	obstacle3Mesh->setType(Mesh::Type::LIGHT);
	obstacle3Mesh->initCubeGeometry();
	obstacle3Mesh->loadTexture(":/grass.png");
	AABB* obstacle3AABB = new AABB(QVector3D(-1 + obstacle3X, -1, obstacle3Z - 1), QVector3D(1 + obstacle3X, 1, obstacle3Z + 1));
	m_physics->addCollider(obstacle3AABB);
	obstacle3->addComponent(obstacle3AABB);
	obstacle3->addComponent(obstacle3Mesh);
	addEntity(mainDecor, obstacle3);

	//4:
	Transform* obstacle4Transform = new Transform(QQuaternion(), QVector3D(obstacle4X, -1, obstacle4Z), 2);
	obstacle4 = new Light("obstacle", obstacle4Transform, QVector4D(1.0, 1.0, 1.0, 1.0));
	Mesh* obstacle4Mesh = new Mesh(GL_TRIANGLE_STRIP);
	obstacle4Mesh->setType(Mesh::Type::LIGHT);
	obstacle4Mesh->initCubeGeometry();
	obstacle4Mesh->loadTexture(":/grass.png");
	AABB* obstacle4AABB = new AABB(QVector3D(-1 + obstacle4X, -1, obstacle4Z - 1), QVector3D(1 + obstacle4X, 1, obstacle4Z + 1));
	m_physics->addCollider(obstacle4AABB);
	obstacle4->addComponent(obstacle4AABB);
	obstacle4->addComponent(obstacle4Mesh);
	addEntity(mainDecor, obstacle4);

	//5:
	Transform* obstacle5Transform = new Transform(QQuaternion(), QVector3D(obstacle5X, -1, obstacle5Z), 2);
	obstacle5 = new Light("obstacle", obstacle5Transform, QVector4D(1.0, 1.0, 1.0, 1.0));
	Mesh* obstacle5Mesh = new Mesh(GL_TRIANGLE_STRIP);
	obstacle5Mesh->setType(Mesh::Type::LIGHT);
	obstacle5Mesh->initCubeGeometry();
	obstacle5Mesh->loadTexture(":/grass.png");
	AABB* obstacle5AABB = new AABB(QVector3D(-1 + obstacle5X, -1, obstacle5Z - 1), QVector3D(1 + obstacle5X, 1, obstacle5Z + 1));
	m_physics->addCollider(obstacle5AABB);
	obstacle5->addComponent(obstacle5AABB);
	obstacle5->addComponent(obstacle5Mesh);
	addEntity(mainDecor, obstacle5);


	//pi�ces: pareil faudrait faire un entity un jour.
	//1: // les pi�ces sont l'une apr�s l'autre dans le graphe de sc�ne en partant de la derni�re (ring1), lorsque l'on collide une pi�ce on la sort de l'�cran, lorsque la derni�re pi�ce passe en -? on fait r�aparaitre toute les pi�ces.

	Mesh* ringMesh = new Mesh(":/sphere.off", Mesh::OFFIO, GL_TRIANGLES);
	ringMesh->loadTexture(":/neige.png");
	
	Transform* ring1Transform = new Transform(QQuaternion(), QVector3D(ringXPos, ringYPos, ringZPos), 0.5f);
	ring1 = new Entity("ring1", ring1Transform);
	BoundingSphere* ring1BS = new BoundingSphere(QVector3D(0.0f, 0.0f, 0.0f), 0.5f);
	m_physics->addCollider(ring1BS);
	ring1->addComponent(ring1BS);
	ring1->addComponent(ringMesh);
	addEntity(mainDecor, ring1);


	//2
	Transform* ring2Transform = new Transform(QQuaternion(), QVector3D(0.0f, decalageRingPosY*ringAboveObstacle, decalageRingPosZ), 1.0f);
	ring2 = new Entity("ring2", ring2Transform);
	BoundingSphere* ring2BS = new BoundingSphere(QVector3D(0.0f, 0.0f, 0.0f), 0.5f);
	m_physics->addCollider(ring2BS);
	ring2->addComponent(ring2BS);
	ring2->addComponent(ringMesh);
	addEntity(ring1, ring2);


	//3
	Transform* ring3Transform = new Transform(QQuaternion(), QVector3D(0.0f, decalageRingPosY * ringAboveObstacle, decalageRingPosZ), 1.0f);
	ring3 = new Entity("ring3", ring3Transform);
	BoundingSphere* ring3BS = new BoundingSphere(QVector3D(0.0f, 0.0f, 0.0f), 0.5f);
	m_physics->addCollider(ring3BS);
	ring3->addComponent(ring3BS);
	ring3->addComponent(ringMesh);
	addEntity(ring2, ring3);
	
	//4
	Transform* ring4Transform = new Transform(QQuaternion(), QVector3D(0.0f, decalageRingPosY * ringAboveObstacle, decalageRingPosZ), 1.0f);
	ring4 = new Entity("ring4", ring4Transform);
	BoundingSphere* ring4BS = new BoundingSphere(QVector3D(0.0f, 0.0f, 0.0f), 0.5f);
	m_physics->addCollider(ring4BS);
	ring4->addComponent(ring4BS);
	ring4->addComponent(ringMesh);
	addEntity(ring3, ring4);
	
	//5
	Transform* ring5Transform = new Transform(QQuaternion(), QVector3D(0.0f, -1*decalageRingPosY * ringAboveObstacle, decalageRingPosZ), 1.0f);
	ring5 = new Entity("ring5", ring5Transform);
	BoundingSphere* ring5BS = new BoundingSphere(QVector3D(0.0f, 0.0f, 0.0f), 0.5f);
	m_physics->addCollider(ring5BS);
	ring5->addComponent(ring5BS);
	ring5->addComponent(ringMesh);
	addEntity(ring4, ring5);

	//6
	Transform* ring6Transform = new Transform(QQuaternion(), QVector3D(0.0f, -1 * decalageRingPosY * ringAboveObstacle, decalageRingPosZ), 1.0f);
	ring6 = new Entity("ring6", ring6Transform);
	BoundingSphere* ring6BS = new BoundingSphere(QVector3D(0.0f, 0.0f, 0.0f), 0.5f);
	m_physics->addCollider(ring6BS);
	ring6->addComponent(ring6BS);
	ring6->addComponent(ringMesh);
	addEntity(ring5, ring6);

	//7
	Transform* ring7Transform = new Transform(QQuaternion(), QVector3D(0.0f, -1 * decalageRingPosY * ringAboveObstacle, decalageRingPosZ), 1.0f);
	ring7 = new Entity("ring7", ring7Transform);
	BoundingSphere* ring7BS = new BoundingSphere(QVector3D(0.0f, 0.0f, 0.0f), 0.5f);
	m_physics->addCollider(ring7BS);
	ring7->addComponent(ring7BS);
	ring7->addComponent(ringMesh);
	addEntity(ring6, ring7);

	//8
	Transform* ring8Transform = new Transform(QQuaternion(), QVector3D(0.0f, -1 * decalageRingPosY * ringAboveObstacle, decalageRingPosZ), 1.0f);
	ring8 = new Entity("ring8", ring8Transform);
	BoundingSphere* ring8BS = new BoundingSphere(QVector3D(0.0f, 0.0f, 0.0f), 0.5f);
	m_physics->addCollider(ring8BS);
	ring8->addComponent(ring8BS);
	ring8->addComponent(ringMesh);
	addEntity(ring7, ring8);


	//9
	Transform* ring9Transform = new Transform(QQuaternion(), QVector3D(0.0f, -1 * decalageRingPosY * ringAboveObstacle, decalageRingPosZ), 1.0f);
	ring9 = new Entity("ring9", ring9Transform);
	BoundingSphere* ring9BS = new BoundingSphere(QVector3D(0.0f, 0.0f, 0.0f), 0.5f);
	m_physics->addCollider(ring9BS);
	ring9->addComponent(ring9BS);
	ring9->addComponent(ringMesh);
	addEntity(ring8, ring9);

	Transform* ring10Transform = new Transform(QQuaternion(), QVector3D(0.0f, -1 * decalageRingPosY * ringAboveObstacle, decalageRingPosZ), 1.0f);
	ring10 = new Entity("ring10", ring10Transform);
	BoundingSphere* ring10BS = new BoundingSphere(QVector3D(0.0f, 0.0f, 0.0f), 0.5f);
	m_physics->addCollider(ring10BS);
	ring10->addComponent(ring10BS);
	ring10->addComponent(ringMesh);
	addEntity(ring9, ring10);
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
	if (player->PointDeVie > 0)
	{
		if (player->justLostPDV) // Si le joueur vient de perdre un point de vie, reset la vitesse.
		{
			scrollingSpeed = initScrollingSpeed;
			player->justLostPDV = false;
		}
		updateTransforms(m_root, deltaTime);
		Transform* transform = mainDecor->getTransform();
		Transform* transformBackGround = background->getTransform();
		Transform* transformY = soleil->getTransform();
		Transform* transformMeteorite = meteorite->getTransform();
		// On fait  ce qui concerne le joueur

		mouvement(transform, deltaTime);
		Jump(transform, deltaTime);
		scrolling(transform, deltaTime);
		transformY->position += QVector3D(0.0f, -initScrollingSpeed * deltaTime, 0.0f);
		if (transformMeteorite->position.y() >= 0)
		{
			if (player->PointDeVie < 2)
			{
				transformMeteorite->position += QVector3D(0.0, -scrollingSpeed * 1.25 * deltaTime, 0.0f);
			}

		}

		scrollingBackGround(transformBackGround, deltaTime);

		mainDecor->setTransform(transform);
		background->setTransform(transformBackGround);
		soleil->setTransform(transformY);


		//   updatePhysics(); <-- fait tout dans le scenegraph
		m_physics->update(deltaTime, m_drawnEntities, player);
	}
	
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

void SceneGraph::scrolling(Transform* transform, TimeStep deltaTime)
{
	//On fait le scrolling:
	transform->position += QVector3D(0.0, 0.0, scrollingSpeed * deltaTime);

	if (transform->position.z() >= 100)
		{
		
		float spawnMeteorite = -(rand() % 4 + 1.5) * initScrollingSpeed;

		obstacle1->getTransform()->position.setX((rand() % 3 - 1) * distanceWhenMoving);
		obstacle2->getTransform()->position.setX((rand() % 3 - 1) * distanceWhenMoving);
		obstacle3->getTransform()->position.setX((rand() % 3 - 1) * distanceWhenMoving);
		obstacle4->getTransform()->position.setX((rand() % 3 - 1) * distanceWhenMoving);
		obstacle5->getTransform()->position.setX((rand() % 3 - 1) * distanceWhenMoving);
		meteorite->getTransform()->position.setX((rand() % 3 - 1) * distanceWhenMoving);


		left->getTransform()->position.setZ(transform->position.z()- left->getTransform()->position.z());
		staticLeft->getTransform()->position.setZ(transform->position.z()- staticLeft->getTransform()->position.z());
		movingLeft->getTransform()->position.setZ(transform->position.z()- movingLeft->getTransform()->position.z());
		staticRight->getTransform()->position.setZ(transform->position.z()- staticRight->getTransform()->position.z());
		right->getTransform()->position.setZ(transform->position.z()- right->getTransform()->position.z());
		movingRight->getTransform()->position.setZ(transform->position.z()- movingRight->getTransform()->position.z());
		
		meteorite->getTransform()->position.setY(100.0f);
		meteorite->getTransform()->position.setZ(spawnMeteorite);



		transform->position = QVector3D(transform->position.x(), transform->position.y(), -100);
		if (scrollingSpeed < maxSpeed)
		{
			scrollingSpeed += acceleration;
			timeWhenMoving = 0.5 * ((maxSpeed - scrollingSpeed) / maxSpeed);
			if (timeWhenMoving == 0.0f)
			{
				timeWhenMoving += 0.1f;
			}
		}
	}
	if (ring1->getTransform()->position.z() > 0.0f)
	{
		ring1->getTransform()->position.setZ(ringZPos);
	}
	if (soleil->getTransform()->position.y() < -10.0f)
	{
		soleil->getTransform()->position.setY(100.0f);
	}
	if (staticLeft->getTransform()->position.z() >= 100)
	{
		float WallPos = 0.0f;
		WallPos = ((rand() % 16)-8) * 5;

		staticLeft->getTransform()->position.setZ(left->getTransform()->position.z()+WallPos);
		staticRight->getTransform()->position.setZ(right->getTransform()->position.z() + WallPos);
	}
	if (movingLeft->getTransform()->position.z() >= 100)
	{
		float WallPos = 0.0f;
		WallPos = ((rand() % 16) - 8) * 5;

		movingLeft->getTransform()->position.setZ(staticLeft->getTransform()->position.z() + WallPos);
		movingRight->getTransform()->position.setZ(staticRight->getTransform()->position.z() + WallPos);
	}
	/*
	if (left->getTransform()->position.z() >= 100)
	{


		left->getTransform()->position.setZ(movingLeft->getTransform()->position.z());
		right->getTransform()->position.setZ(movingRight->getTransform()->position.z());
	}*/

}


void SceneGraph::scrollingBackGround(Transform* transform, TimeStep deltaTime)
{
	//On fait le scrolling:
	transform->position += QVector3D(10.5f * deltaTime, 0.0, 0.0f);

	if (transform->position.x() >= 10)
	{

		transform->position = QVector3D(-30.0f, transform->position.y(), transform->position.z());

	}

}

void SceneGraph::mouvement(Transform* transform, TimeStep deltaTime)
{


	if (distMoved >= distanceWhenMoving)
	{
		isMovingLeft = false;
		isMovingRight = false;

		player->isMovingLeft = false;
		player->isMovingRight = false;
		distMoved = 0.0f;
	}

	// on regarde sur quel rail est le joueur s'il n'est pas entrain de bouger.
	if (!isMovingRight && !isMovingLeft)
	{
		if (transform->position.x() < 4.0f && transform->position.x() > -4.0f)
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



	// on d�place le joueur selon son rail et son mouvement
	float deplacement = (distanceWhenMoving / timeWhenMoving) * deltaTime;


	if (isMovingLeft && !isMovingRight && !joueur_rl)
	{
		distMoved += deplacement;
		std::cout << "moving left";
		transform->position += QVector3D(deplacement, 0.0, 0.0);

		player->isMovingLeft = true;
		player->isMovingRight = false;


	}
	if (isMovingRight && !isMovingLeft && !joueur_rr)
	{
		distMoved += deplacement;
		std::cout << "moving right";
		transform->position += QVector3D(-deplacement, 0.0, 0.0);

		player->isMovingLeft = false;
		player->isMovingRight = true;

	}



	

}
void SceneGraph::Jump(Transform *transform, TimeStep deltaTime)
{
	//On fait le saut:

	if (isJumping)
	{
		if (transform->position.y() > -tailleJump)
		{
			transform->position += QVector3D(0.0f, (-tailleJump / timeJumping) * deltaTime, 0.0f);
		}
		else
		{
			transform->position.setY(-tailleJump);
			isJumping = false;
			player->isJumping = false;
			isFalling = true;
			player->hasJumped = true;
		}
	}
	if (isFalling)
	{
		if (transform->position.y() < 0.0f)
		{
			transform->position += QVector3D(0.0f, (tailleJump / timeFalling) * deltaTime, 0.0f);
		}
		else
		{
			transform->position.setY(0.0f);
			isJumping = false;
			player->isJumping = false;
			isFalling = false;
			player->hasJumped = false;
		}
	}

}

void SceneGraph::MakeAnObstacle(float z) //c'est pas une vrai fonction c'est pour faire des copier coller
{ // Il faut aussi ajouter Entity* obstacleX dans le hpp 
	Transform* obstacle4Transform = new Transform(QQuaternion(), QVector3D(obstacle4X, -1, obstacle4Z), 2);
	obstacle4 = new Light("obstacle4", obstacle4Transform, QVector4D(1.0, 1.0, 1.0, 1.0));
	Mesh* obstacle4Mesh = new Mesh(GL_TRIANGLE_STRIP);
	obstacle4Mesh->setType(Mesh::Type::LIGHT);
	obstacle4Mesh->initCubeGeometry();
	obstacle4Mesh->loadTexture(":/grass.png");
	AABB* obstacle4AABB = new AABB(QVector3D(-1+obstacle4X, -1, obstacle4Z-1), QVector3D(1+obstacle4X, 1, obstacle4Z+1));
	m_physics->addCollider(obstacle4AABB);
	obstacle4->addComponent(obstacle4AABB);
	obstacle4->addComponent(obstacle4Mesh);
	addEntity(mainDecor, obstacle4);
}

/*void SceneGraph::MakeARing(float z) // pas une vraie fonction non plus
{
	Transform* ring10Transform = new Transform(QQuaternion(), QVector3D(0.0f, 1.0f + ringAboveObstacle * 8 * (tailleJump / timeJumping) / 60, initRingPos - 8 * initScrollingSpeed / 60),0.5f);
	ring10 = new Light("ring10", ring10Transform, QVector4D(1.0, 1.0, 1.0, 1.0));
	BoundingSphere* ring10BS = new BoundingSphere(QVector3D(0.0f, 0.0f, 0.0f), 0.5f);
	m_physics->addCollider(ring10BS);
	ring10->addComponent(ring10BS);
	ring10->addComponent(ringMesh);
	addEntity(sol, ring10);
}*/