//
// Created by Maxime Boucher on 27/11/2021.
//

#include "TargetFPS.hpp"

/**
 * Par défaut: VSync et FPS cap (macos) à 60
 */
TargetFPS::TargetFPS() {
	this->targetFPS = 60;
	this->swapInterval = 1;
}

/**
 * Initialise les fps et la vsync pour linux, windows, macos
 * @param fps
 */
TargetFPS::TargetFPS(int fps) {
	if (fps <= 0) {
		this->targetFPS = 1000000.0;
		this->swapInterval = 0;
	} else {
		this->targetFPS = fps;
		this->swapInterval = 1/(targetFPS/60);
	}
}

/**
 * Renvoit le temps en millisecondes d'une frame.
 * Utile pour macOS en particulier où la synchro verticale seule ne fonctionne pas pour limiter les FPS.
 * @return 1000/targetFPS
 */
float TargetFPS::getTimePerFrame() const {
	return 1000/targetFPS;
}

/**
 * Renvoit l'intervalle de synchronisation verticale.
 * Utile pour limiter les FPS sur Windows/Linux
 * @return swapInterval
 */
int TargetFPS::getSwapInterval() const {
	return swapInterval;
}
