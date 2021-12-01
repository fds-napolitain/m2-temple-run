#ifndef SCENE_H
#define SCENE_H

#include "entity.hpp"
#include "mesh.hpp"
#include "geometryengine.hpp"
#include "TimeStep.hpp"

#include "physics/RigidBody.hpp"
#include "physics/physicsengine.hpp"
#include "physics/PhysicSystem.hpp"

class Scene
{
public:
    Scene();
    virtual ~Scene();
    PhysicSystem *m_physics = new PhysicSystem;
    std::vector<Entity*> m_drawnEntities; // objects to draw
    std::vector<Entity*> m_physXentities; // physics of entities
    virtual void draw(GeometryEngine* gEngine, QOpenGLShaderProgram& shaderProgram); //maybe virtual if draw depends of the type scene
    virtual void update(TimeStep timeStep){};

};

#endif // SCENE_H
