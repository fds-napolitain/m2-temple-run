//
// Created by Maxime Boucher on 26/12/2021.
//

#ifndef TEMPLERUN_KEYBOARDEVENTS_HPP
#define TEMPLERUN_KEYBOARDEVENTS_HPP


#include "source/engine/components/component.hpp"

class KeyboardEvents : public Component {
public:
	int getType() override;
};


#endif //TEMPLERUN_KEYBOARDEVENTS_HPP
