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
    float initScrollingSpeed = 14.0f;
    float scrollingSpeed = initScrollingSpeed;
    float acceleration = 1.0f;
    float maxSpeed = 24.0f;

    //variable du saut
    bool isJumping = false;
    bool isFalling = false;

    float tailleJump = 10.0f;
    float timeJumping = 0.25f;
    float timeFalling = 4*timeJumping;


    //obstacle:
    float obstacle1X = 0.0f;
    float obstacle2X = distanceWhenMoving;
    float obstacle3X = -distanceWhenMoving;
    float obstacle4X = 0.0f;
    float obstacle5X = distanceWhenMoving;

    float obstacle1Z = initScrollingSpeed;;
    float obstacle2Z = -1 * initScrollingSpeed;
    float obstacle3Z = -2 * initScrollingSpeed;
    float obstacle4Z = -3 * initScrollingSpeed;
    float obstacle5Z = -4 * initScrollingSpeed;





    Entity* getRoot();
    void scrolling(Transform* transform, TimeStep deltaTime);
    void mouvement(Transform* transform, TimeStep deltaTime);
    void Jump(Transform* transform, TimeStep deltaTime);
    void MakeAnObstacle(float z);
    void addEntity(Entity* parent, Entity* entity);
    void updateTransforms(Entity* root_node, TimeStep deltaTime);
	Entity *mainDecor;
    Light *obstacle1;
    Light *obstacle2;
    Light *obstacle3;
    Light *obstacle4;
    Light  *obstacle5;
    
    Player *player;

private:
    
    Entity *m_root;

};

#endif // SCENEGRAPH_H
