#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "scene.hpp"
#include "entity.hpp"


class SceneGraph : public Scene
{
public:
    explicit SceneGraph(Entity *root) :
        Scene(),
        m_root(root)
    {
        Transform* soleilTransform = new Transform(QQuaternion(), QVector3D(0,1,0), 1);
        Transform* solT = new Transform(QQuaternion(), QVector3D(0,-2.0,0), 1);
        Transform *luneTransform = new Transform(QQuaternion(), QVector3D(2,0,0), 0.5);
        Transform* terreTransform = new Transform(QQuaternion(), QVector3D(2,0,0), 1);

        Entity* soleil = new Entity("soleil", soleilTransform );
        Entity* terre = new Entity("Terre", terreTransform);
        Entity* lune = new Entity("lune", luneTransform);
        Entity* sol = new Entity("Sol", solT);

        Mesh* solMesh = new Mesh(":/sphere.off", Mesh::OFFIO, GL_POINTS);
       // solMesh->initPlaneGeometry(8,8,5,5);

        Mesh* sphere = new Mesh(":/sphere.off", Mesh::OFFIO, GL_POINTS);
//
        BoundingSphere* a = new BoundingSphere(soleilTransform->position, soleilTransform->scale);
        BoundingSphere* b = new BoundingSphere(solT->position, solT->scale);
        RigidBody* rb = new RigidBody(a);
        m_physics->addRigidBody(rb);

        m_physics->addCollider(a);
        m_physics->addCollider(b);
        soleil->addComponent(rb);
        sol->addComponent(solMesh);
        soleil->addComponent(sphere);
        terre->addComponent(sphere);
        lune->addComponent(sphere);

        addEntity(m_root, sol);
        addEntity(m_root, soleil);
        addEntity(soleil, terre);
        addEntity(terre, lune);


        //m_entities.emplace_back(root);
    }

    ~SceneGraph() override
    {
        delete m_root;
    }

    void update(TimeStep timeStep) override;
    inline Entity* getRoot()  {return m_root; }
    void addEntity(Entity* parent, Entity* entity);
    void updateTransforms(Entity* root_node, TimeStep deltaTime);


private:

    Entity *m_root;
};

#endif // SCENEGRAPH_H
