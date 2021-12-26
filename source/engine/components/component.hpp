#ifndef COMPONENT_H
#define COMPONENT_H


class Component {

public:
	enum Type {
		NONE, // NONE
		MESH, // RENDERING
		ANIMATION,
		COLLIDER, // PHYSICS
		KEYBOARD_EVENTS, // EVENTS
	};

    Component();
    virtual ~Component()= default;
	virtual int getType();

};

#endif // COMPONENT_H
