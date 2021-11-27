//
// Created by Maxime Boucher on 27/11/2021.
//

#ifndef TEMPLERUN_TARGETFPS_HPP
#define TEMPLERUN_TARGETFPS_HPP


class TargetFPS {

private:
	float targetFPS;
	int swapInterval;
public:
	explicit TargetFPS(int fps);
	[[nodiscard]] float getTimePerFrame() const;
	[[nodiscard]] int getSwapInterval() const;

};

#endif //TEMPLERUN_TARGETFPS_HPP
