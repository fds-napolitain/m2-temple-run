#ifndef SCENE_H
#define SCENE_H

#include "entity.hpp"
#include "mesh.hpp"
#include "geometryengine.hpp"
#include "source/engine/TimeStep.hpp"

#include "source/engine/physics/PhysicSystem.hpp"

class Scene
{
public:
    Scene();
    virtual ~Scene();
    void draw(GeometryEngine* gEngine, QOpenGLShaderProgram& shaderProgram, QOpenGLShaderProgram& lightProgram, QOpenGLShaderProgram& HMProgram);
    PhysicSystem *m_physics = new PhysicSystem;
    std::vector<Entity*> m_drawnEntities; // objects to draw
    std::vector<Entity*> m_physXentities; // physics of entities
    //virtual void draw(GeometryEngine* gEngine, QOpenGLShaderProgram& shaderProgram, QOpenGLShaderProgram& lightProgram); //maybe virtual if draw depends of the type scene
    virtual void update(TimeStep timeStep){};

};

#endif // SCENE_H
