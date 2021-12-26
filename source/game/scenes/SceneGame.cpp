//
// Created by Maxime Boucher on 26/12/2021.
//

#include "SceneGame.hpp"

SceneGame::SceneGame() : SceneGraph() {
	player = new Player("player");
	Transform* solTransform = new Transform(QQuaternion(), QVector3D(0, -4.0, 0), 1);
	Transform* rightTransform = new Transform(QQuaternion::fromAxisAndAngle(0.0, 0.0, 1.0, 90), QVector3D(7, -2.0, 0), 1);
	Transform* leftTransform = new Transform(QQuaternion::fromAxisAndAngle(0.0, 0.0, -1.0, 90), QVector3D(-7, -2.0, 0), 1);
	Transform* mainDecorTransform = new Transform(QQuaternion::fromAxisAndAngle(0.0, 0.0, 0.0,  0), QVector3D(0, 0.0, -100), 1);
	Transform* backgroundTransform = new Transform(QQuaternion::fromAxisAndAngle(1.0, 0.0, 0.0, 90), QVector3D(0, 0.0, -105), 1);
	Transform* obstacleTransform = new Transform(QQuaternion(), QVector3D(0,-1,0), 2);

	Transform* mainDecorAnimation = new Transform(QQuaternion(), QVector3D(0.0, 0.0, 8.0));

	Entity* sol = new Entity("sol", solTransform);
	Entity* right = new Entity("right", rightTransform);
	Entity* left = new Entity("left", leftTransform);
	Entity* mainDecor = new Entity("mainDecor", mainDecorTransform, mainDecorAnimation);
	Entity* obstacle = new Entity("obstacle", obstacleTransform);
	Entity* background = new Entity("fond", backgroundTransform);

	Mesh* solMesh = new Mesh(GL_TRIANGLE_STRIP);
	solMesh->loadTexture(":/neige.png");

	Mesh* rightMesh = new Mesh(GL_TRIANGLE_STRIP);
	rightMesh->loadTexture(":/rock.png", QOpenGLTexture::LinearMipMapLinear);

	Mesh* leftMesh = new Mesh(GL_TRIANGLE_STRIP);

	Mesh* backgroundMesh = new Mesh(GL_TRIANGLE_STRIP);

	Mesh* obstacleMesh = new Mesh(GL_TRIANGLE_STRIP);
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


	Transform* scoreTransform = new Transform(QQuaternion(), QVector3D(3,3,0), 0.2);
	Entity* score = new Entity("score", scoreTransform);
	Mesh* scoreMesh = new Mesh(":/0.off", Mesh::OFFIO, GL_TRIANGLES);
	scoreMesh->loadTexture(":/neige.png");
	score->addComponent(scoreMesh);

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
	addEntity(m_root, score);
}

void SceneGame::keyPressEvent(QKeyEvent *event, TimeStep step) {
	Transform* transform = player->getTransform();
	switch (event->key()) {
		case Qt::Key_Left:
			transform->position += QVector3D(-1.0, 0.0, 0.0) * step;
			player->setTransform(transform);
			break;
		case Qt::Key_Right:
			transform->position += QVector3D(1.0, 0.0, 0.0) * step;
			player->setTransform(transform);
			break;
	}
}
