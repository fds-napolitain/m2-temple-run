#ifndef COMPONENT_H
#define COMPONENT_H

/**
 * Classe composant (virtuel) : peut être n'importe quel "plugin" à une entité.
 */
class Component {

public:
    Component();
    virtual ~Component()= default;;
    virtual int getCType();

};

/**
 * Enumération des type de composants
 */
enum CType {
	NONE,
	COLLIDER,
	ANIMATION,
	MESH,
};

#endif // COMPONENT_H
