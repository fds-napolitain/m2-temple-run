//
// Created by Maxime Boucher on 25/12/2021.
//

#include "TimeStep.hpp"

/**
 * Crée un objet timestep / deltatime
 * @param time
 */
TimeStep::TimeStep(float time) : m_time(time) {

}

/**
 * Renvoit m_time en millisecondes
 * @return
 */
float TimeStep::getTMilliSeconds() const {
	return m_time * 1000.0f;
}

/**
 * Renvoit m_time en secondes
 * @return
 */
float TimeStep::getSeconds() const {
	return m_time;
}

/**
 * Cast implicite et explicite en float renvoit m_time
 * @return
 */
TimeStep::operator float() const {
	return m_time;
}
