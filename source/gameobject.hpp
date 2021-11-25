#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "component.hpp"
#include "transform.hpp"
#include "geometryengine.hpp"
#include <iostream>
#include <QOpenGLTexture>

class GameObject
{
private:
	std::string name;
	GameObject* parent;
	std::vector<GameObject*> children;
public:
	Transform transform;
    Transform animation;
    GeometryEngine* engine;
    GameObject();
	explicit GameObject(GameObject* parent);
	~GameObject();
	GameObject(GameObject* parent, const Transform& transform);
	GameObject(GameObject* parent, const Transform& transform, const std::string& mesh);
    GameObject(const std::string& name, GameObject* parent, const Transform& transform, const std::string& mesh, Transform animation);
    GameObject(const std::string& name, GameObject* parent, const Transform& transform, Transform animation);
    GameObject(GameObject* parent, const Transform& transform, const std::string& mesh, Transform animation, const std::string& texture);
	std::string getName();
    void addComponent(Component component);
    void addChild(GameObject* gameObject); // add child
	GameObject* getParent();
    void removeChild(const std::string& name); // remove child by name
    void remove_component(const std::string& name);
	void updateObject(QOpenGLShaderProgram& program, float deltaTime = 10);
};

#endif // GAMEOBJECT_H
