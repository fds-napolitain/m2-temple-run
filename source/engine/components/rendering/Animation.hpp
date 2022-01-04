//
// Created by Maxime Boucher on 04/01/2022.
//

#ifndef TEMPLERUN_ANIMATION_HPP
#define TEMPLERUN_ANIMATION_HPP


#include "source/engine/components/component.hpp"
#include "source/engine/transform.hpp"

class Animation : public Component {

private:
	Transform transform;
public:
	explicit Animation(Transform transform);
	~Animation() override = default;
	int getCType() override;

};


#endif //TEMPLERUN_ANIMATION_HPP
