#include "component.hpp"

Component::Component() = default;

/**
 * Renvoit le type du component (ou ID).
 * @return
 */
int Component::getType() {
	return Type::NONE;
}
