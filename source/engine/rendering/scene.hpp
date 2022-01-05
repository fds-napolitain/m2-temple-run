#ifndef SCENE_H
#define SCENE_H

#include "entity.hpp"
#include "mesh.hpp"
#include "geometryengine.hpp"
#include "source/engine/TimeStep.hpp"

#include "source/engine/physics/PhysicSystem.hpp"

/**
 * Classe scène, qui permet de dessiner les objets. La méthode update est virtuel : elle est implémentée différemment selon le type de scène (graphe de scene ou autre).
 */
class Scene {

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
