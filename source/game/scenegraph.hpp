#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "source/engine/rendering/scene.hpp"
#include "source/engine/rendering/Light.hpp"
#include "Player.hpp"
#include <QTime>
#include "source/engine/components/physics/collider/aabb.hpp"

/**
 * Graphe de scène:
 * - définition du graphe de scène. Update() est la gameloop
 */
class SceneGraph : public Scene {
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


    //variables sur le d�placement
    float distanceWhenMoving = 5.0f;
    float timeWhenMoving = 0.5f;
    float initScrollingSpeed = 18.0f;
    float scrollingSpeed = initScrollingSpeed;
    float acceleration = 5.0f;
    float maxSpeed = 220.0f;
    float tempSpeed = 0.0f; //permet de freeze le jeu pour pouvoir faire la d�mo.

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

    float obstacle1Z = 0.0f;
    float obstacle2Z = -1 * initScrollingSpeed;
    float obstacle3Z = -2 * initScrollingSpeed;
    float obstacle4Z = -3 * initScrollingSpeed;
    float obstacle5Z = -4 * initScrollingSpeed;





    Entity* getRoot();
    void scrolling(Transform* transform, TimeStep deltaTime);
    void scrollingBackGround(Transform* transform, TimeStep deltaTime);
    void mouvement(Transform* transform, TimeStep deltaTime);
    void jump(Transform* transform, TimeStep deltaTime);
    void makeAnObstacle(float z);
    void makeARing(float z);
    void addEntity(Entity* parent, Entity* entity);
    void updateTransforms(Entity* root_node, TimeStep deltaTime);
	void updateScore(Entity* scoreX, int value);

	Entity *mainDecor;
    Entity  *background;
    Entity* left;
    Entity* right;
    Entity* staticLeft;
    Entity* movingLeft;
    Entity* staticRight;
    Entity* movingRight;
    Entity* meteorite;
    Light *obstacle1;
    Light *obstacle2;
    Light *obstacle3;
    Light *obstacle4;
    Light  *obstacle5;

    Light* soleil;
    


    
    float ringAboveObstacle = 0.0f; //1 v 0 f
    float ringXPos = 0.0f;
    float ringYPos = 0.0f;
    float ringZPos = -1.5f * initScrollingSpeed;

    float decalageRingPosY = tailleJump / 20 ;
    float decalageRingPosZ = initScrollingSpeed / 2;

    Entity* ring1;
    Entity* ring2;
    Entity* ring3;
    Entity* ring4;
    Entity* ring5;
    Entity* ring6;
    Entity* ring7;
    Entity* ring8;
    Entity* ring9;
    Entity* ring10;

	Light* score1;
	Light* score2;
	Light* score3;
	Light* score4;
	Mesh* score0Mesh;
	Mesh* score1Mesh;
	Mesh* score2Mesh;
	Mesh* score3Mesh;
	Mesh* score4Mesh;
	Mesh* score5Mesh;
	Mesh* score6Mesh;
	Mesh* score7Mesh;
	Mesh* score8Mesh;
	Mesh* score9Mesh;


    Player *player;

private:
    
    Entity *m_root;

};

#endif // SCENEGRAPH_H
