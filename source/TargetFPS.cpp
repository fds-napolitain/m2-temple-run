//
// Created by Maxime Boucher on 27/11/2021.
//

#include "TargetFPS.hpp"

TargetFPS::TargetFPS(int fps) {
	if (fps <= 0) {
		this->targetFPS = 1000000.0;
		this->swapInterval = 0;
	} else {
		this->targetFPS = fps;
		this->swapInterval = 1.0/(targetFPS/60.0);
	}
}

 float TargetFPS::getTimePerFrame() const {
	return 1000/targetFPS;
}

int TargetFPS::getSwapInterval() const {
	return swapInterval;
}
