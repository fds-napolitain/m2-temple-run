//
// Created by Maxime Boucher on 26/12/2021.
//

#ifndef TEMPLERUN_ANIMATION_HPP
#define TEMPLERUN_ANIMATION_HPP


#include "source/engine/components/component.hpp"
#include "source/engine/transform.hpp"

class Animation : public Component {

private:
	Transform position;

public:
	explicit Animation(Transform position);
	[[nodiscard]] const Transform &getPosition() const;
	int getType() override;

};


#endif //TEMPLERUN_ANIMATION_HPP
