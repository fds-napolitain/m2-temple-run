//
// Created by Maxime Boucher on 25/12/2021.
//

#include "TimeStep.hpp"

TimeStep::TimeStep(float time) : m_time(time) {

}

float TimeStep::getTMilliSeconds() const {
	return m_time * 1000.0f;
}

float TimeStep::getSeconds() const {
	return m_time ;
}

TimeStep::operator float() const {
	return m_time;
}
