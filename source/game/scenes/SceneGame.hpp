//
// Created by Maxime Boucher on 26/12/2021.
//

#ifndef TEMPLERUN_SCENEGAME_HPP
#define TEMPLERUN_SCENEGAME_HPP


#include "source/engine/scenegraph.hpp"

class SceneGame : public SceneGraph {

private:
	Player* player;
public:
	SceneGame();
	void keyPressEvent(QKeyEvent *event, TimeStep step) override;
	void update(TimeStep timeStep) override;

};


#endif //TEMPLERUN_SCENEGAME_HPP
