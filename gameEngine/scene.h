#ifndef SCENE_H
#define SCENE_H

#include "physics/physicobject.h"
#include "physics/physicsengine.h"
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
    std::vector<Entity*> m_entities; // all sort of entities
    void draw(GeometryEngine* gEngine, QOpenGLShaderProgram& shaderProgram); //maybe virtual if draw depends of the type scene

};

#endif // SCENE_H
