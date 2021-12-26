//
// Created by Maxime Boucher on 26/12/2021.
//

#include "Animation.hpp"

Animation::Animation(Transform position) {
	this->position = position;
}

int Animation::getType() {
	return Type::ANIMATION;
}

const Transform &Animation::getPosition() const {
	return position;
}
