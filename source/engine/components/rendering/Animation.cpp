//
// Created by Maxime Boucher on 04/01/2022.
//

#include "Animation.hpp"

/**
 * Initialise une animation à partir d'une transform
 * @param transform qui sera combineWith() à chaque update sur la transform position de l'objet entité courant.
 */
Animation::Animation(Transform* transform) {
	this->transform = *transform;
}

/**
 * Animation est un Component::ANIMATION
 * @return
 */
int Animation::getCType() {
	return ANIMATION;
}
