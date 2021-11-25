#ifndef SCENE_H
#define SCENE_H

#include "../gameEngine/physics/physicobject.h"
#include "../gameEngine/physics/physicsengine.h"
#include "entity.h"
#include "mesh.h"
#include "geometryengine.h"

class Scene
{
public:
    Scene();
    virtual ~Scene();
    PhysicsEngine *m_physics;
    std::vector<Entity*> m_drawnEntities; // objects to draw
    std::vector<Entity*> m_physXentities; // physics of entities
    virtual void draw(GeometryEngine* gEngine, QOpenGLShaderProgram& shaderProgram); //maybe virtual if draw depends of the type scene
    virtual void update(){};

};

#endif // SCENE_H
