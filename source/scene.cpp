//
// Created by Maxime Boucher on 06/11/2021.
//

#include "scene.hpp"

/**
 * Creation of scene
 */
Scene::Scene() {
	// centre du monde (orbite, noeud soleil mais vide)
    world = new GameObject();

	// animations
	Transform null = Transform(QQuaternion(), QVector3D(), 1.0f);
	Transform rotateY = Transform(QQuaternion::fromAxisAndAngle(0.f, 1.0, 0.0, 0.05), QVector3D(), 1.0f);
	Transform rotateZ = Transform(QQuaternion::fromAxisAndAngle(0.f, 0.0, 1.0, 0.05), QVector3D(), 1.0f);

	// objet soleil
	GameObject* soleil = new GameObject("soleil", world, null, ":/sphere.off", rotateY.inverse());
	// orbite terre centrée sur noeud soleil
	GameObject* orbiteTerre = new GameObject("orbite terre", world, null, rotateY);
    // noeud terre, centrée sur orbite terre sans rotation avec scaling et translation
	GameObject* noeudTerre = new GameObject(orbiteTerre, Transform(QQuaternion(), QVector3D(2.0, 0.0, 0.0), 0.33));
	// objet terre, centrée sur noeud terre avec rotation
	GameObject* terre = new GameObject("terre", noeudTerre, null, ":/sphere.off", Transform(QQuaternion(0.0, 0.0, 0.22, 0.0)));

	// pareil lune
	GameObject* orbiteLune = new GameObject("noeud lune", noeudTerre, null, rotateY);
	GameObject* noeudLune = new GameObject(orbiteLune, Transform(QQuaternion(), QVector3D(-1.5, 0.0, 0), 0.33));
	GameObject* lune = new GameObject("lune", noeudLune, null, ":/sphere.off", rotateY);
}

/**
 * Call delete on world (parent of gameobjects) which is recursive.
 */
Scene::~Scene() {
	delete world;
}

/**
 * Update of scene
 */
void Scene::updateScene(QOpenGLShaderProgram& program) {
    world->updateObject(program);
}
