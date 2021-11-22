#ifndef SCENE_H
#define SCENE_H

#include "physics/physicobject.h"
#include "physics/physicsengine.h"
#include "entity.h"

class Scene
{
public:
    Scene();
    virtual ~Scene();
    PhysicsEngine *m_physics;
    std::vector<Entity*> m_drawnEntities; // objects to draw
    std::vector<Entity*> m_entities; // all sort of entities

};

#endif // SCENE_H
