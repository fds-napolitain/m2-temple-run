//
// Created by Maxime Boucher on 26/12/2021.
//

#ifndef TEMPLERUN_SCENEGAME_HPP
#define TEMPLERUN_SCENEGAME_HPP


#include "source/engine/rendering/scenegraph.hpp"

class SceneGame : public SceneGraph {

private:
	Player* player;
public:
	SceneGame();
	void keyPressEvent(QKeyEvent *event, TimeStep step) override;

};


#endif //TEMPLERUN_SCENEGAME_HPP
