//
// Created by Maxime Boucher on 04/01/2022.
//

#include "Animation.hpp"

Animation::Animation(Transform transform) {
	this->transform = transform;
}

int Animation::getCType() {
	return ANIMATION;
}
