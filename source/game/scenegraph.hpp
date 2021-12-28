#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "source/engine/rendering/scene.hpp"
#include "source/engine/rendering/Light.hpp"
#include "Player.hpp"
#include <QTime>


class SceneGraph : public Scene
{
public:
    SceneGraph(Entity *root);
    ~SceneGraph() override;
    void update(TimeStep timeStep) override;

    // position du joueur sur les rails
    bool joueur_rl = false;  
    bool joueur_rm = false;
    bool joueur_rr = false;

    //mouvement du joueur:
    bool isMovingLeft = false;
    bool isMovingRight = false;

    //compteur de mouvement
    float distMoved = 0.0f;


    //variables sur le déplacement
    float distanceWhenMoving = 5.0f;
    float timeWhenMoving = 0.5f;

    //variable du saut
    bool isJumping = false;
    bool hasJumped = false;

    float tailleJump = 5.0f;
    float tempsJump = 0.5f;


    Entity* getRoot();
    void addEntity(Entity* parent, Entity* entity);
    void updateTransforms(Entity* root_node, TimeStep deltaTime);
	Entity *mainDecor;
    
    Player *player;

private:
    
    Entity *m_root;

};

#endif // SCENEGRAPH_H
