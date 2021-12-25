//
// Created by Maxime Boucher on 25/12/2021.
//

#ifndef TEMPLERUN_PREFABS_HPP
#define TEMPLERUN_PREFABS_HPP


#include "entity.hpp"

class Prefabs : public Entity {

private:
	std::vector<Entity> entities;

public:
	Prefabs();

};


#endif //TEMPLERUN_PREFABS_HPP
