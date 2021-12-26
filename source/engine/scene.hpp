#ifndef SCENE_H
#define SCENE_H

#include "source/engine/rendering/entity.hpp"
#include "source/engine/rendering/mesh.hpp"
#include "source/engine/rendering/geometryengine.hpp"
#include "source/engine/TimeStep.hpp"

#include "source/engine/physics/PhysicSystem.hpp"

class Scene
{
public:
    Scene();
    virtual ~Scene();
    PhysicSystem *m_physics = new PhysicSystem;
    std::vector<Entity*> m_drawnEntities; // objects to draw
    std::vector<Entity*> m_physXentities; // physics of entities
    virtual void draw(GeometryEngine* gEngine, QOpenGLShaderProgram& shaderProgram, QOpenGLShaderProgram& lightProgram); //maybe virtual if draw depends of the type scene
    virtual void update(TimeStep timeStep){};

};

#endif // SCENE_H
