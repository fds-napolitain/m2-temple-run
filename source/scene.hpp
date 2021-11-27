#ifndef SCENE_H
#define SCENE_H

#include "physics/physicobject.hpp"
#include "physics/physicsengine.hpp"
#include "entity.hpp"
#include "mesh.hpp"
#include "geometryengine.hpp"
#include "TimeStep.hpp"

class Scene
{
public:
    Scene();
    virtual ~Scene();
    PhysicsEngine *m_physics{};
    std::vector<Entity*> m_drawnEntities; // objects to draw
    std::vector<Entity*> m_physXentities; // physics of entities
    virtual void draw(GeometryEngine* gEngine, QOpenGLShaderProgram& shaderProgram); //maybe virtual if draw depends of the type scene
    virtual void update(TimeStep timeStep){};

};

#endif // SCENE_H
