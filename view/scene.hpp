//
// Created by Maxime Boucher on 06/11/2021.
//

#ifndef CUBE_SCENE_HPP
#define CUBE_SCENE_HPP

#include <model/gameobject.hpp>

class Scene {
private:
    GameObject* world;
public:
	Scene();
	~Scene();
	void updateScene(QOpenGLShaderProgram& program);
};


#endif //CUBE_SCENE_HPP
