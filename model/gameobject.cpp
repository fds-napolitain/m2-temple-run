#include "gameobject.hpp"

/**
 * Créé un gameobject sans l'ajouter à un parent
 */
GameObject::GameObject() {
	parent = nullptr;
    engine = new GeometryEngine();
	transform = Transform();
}

/**
 * Ajoute un gameobject au parent donné
 * @param parent
 */
GameObject::GameObject(GameObject *parent) {
    std::cout  << "GO:GO(" << parent <<")" << std::endl;
    this->parent = parent;
	this->parent->addChild(this);
    engine = new GeometryEngine();
	this->transform = Transform();
}

/**
 * Ajoute un gameobject contenant une transform au parent donné
 * @param parent
 * @param transform
 */
GameObject::GameObject(GameObject *parent, const Transform& transform) {
    std::cout  << "GO:GO(" << parent <<","<< &transform << ")" << std::endl;
    this->parent = parent;
    this->parent->addChild(this);
    engine = new GeometryEngine();
    this->transform = transform;
}

/**
 * Ajoute un gameobject contenant une transform et un mesh au parent donné
 * @param parent
 * @param transform
 * @param mesh
 */
GameObject::GameObject(GameObject *parent, const Transform& transform, const std::string& mesh) {
    std::cout  << "GO:GO(" << parent <<","<< &transform<<","<< mesh << ")" << std::endl;
    this->parent = parent;
	this->parent->addChild(this);
	engine = new GeometryEngine();
	engine->initMesh(mesh);
	this->transform = transform;
}

GameObject::GameObject(const std::string& name, GameObject *parent, const Transform& transform, const std::string& mesh, Transform animation) {
    std::cout << "*** GO:GO with Animation(" << name << "," << parent << "," << &transform << "," << mesh << "," << &animation << ")" << std::endl;
    this->name = name;
    this->parent = parent;
    this->parent->addChild(this);
    engine = new GeometryEngine();
    engine->initMesh(mesh);
    this->transform = transform;
    this->animation = animation;
    // add better texture control
}

GameObject::GameObject(const std::string &name, GameObject *parent, const Transform &transform, Transform animation) {
	this->name = name;
	this->parent = parent;
	this->parent->addChild(this);
	engine = new GeometryEngine();
	this->transform = transform;
	this->animation = animation;
}

GameObject::GameObject(GameObject *parent, const Transform& transform, const std::string& mesh, Transform animation, const std::string& texture) {
    std::cout  << "GO:GO(" << parent <<","<< &transform<<","<< mesh <<","<< &animation << ","<< texture << ")" << std::endl;
    this->parent = parent;
	this->parent->addChild(this);
	engine = new GeometryEngine();
	engine->initMesh(mesh);
	this->transform = transform;
	this->animation = animation;
    // add better texture control
}

/**
 * Delete game object and all its children
 */
GameObject::~GameObject() {
	for (const auto &child: children) {
		delete child;
	}
    delete engine;
}

/**
 * Ajoute un fils dans la liste children d'un parent
 * @param gameObject
 */
void GameObject::addChild(GameObject* gameObject) {
    children.push_back(gameObject);
}

/**
 * Supprime un fils de la liste children d'un parent
 * @param name
 */
void GameObject::removeChild(const std::string& name) {
    for (int i = 0; i < children.size(); i++) {
        if (children[i]->name == name) {
            children.erase(children.begin() + i);
        }
    }
}

/**
 * Retourne le nom du gameobject
 * @return
 */
std::string GameObject::getName() {
	return name;
}

/**
 * Draw every game objects from top to bottom
 * @param program
 */
void GameObject::updateObject(QOpenGLShaderProgram& program, float deltaTime) {
	if (parent == nullptr) { // position globale
		this->transform.matrix = this->transform.getLocalMatrix();
	} else {
		this->transform.matrix = this->parent->transform.matrix * this->transform.getLocalMatrix();
	}
	this->transform.combineWith(this->animation); // animation locale

	// charger shader
	program.setUniformValue("transform_matrix", this->transform.matrix * deltaTime);

    // draw
	engine->drawGeometry(&program);

    // recursive: children
	for (const auto &child: children) {
		child->updateObject(program);
	}
}

/**
 * Retourne le parent
 * @return
 */
GameObject *GameObject::getParent() {
	return parent;
}
