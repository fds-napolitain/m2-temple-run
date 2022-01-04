#include "component.hpp"

/**
 * Constructeur par défaut
 */
Component::Component() = default;

/**
 * Renvoit le type de component
 * @return
 */
int Component::getCType() {
	return NONE;
}
