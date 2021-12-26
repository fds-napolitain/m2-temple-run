#ifndef COMPONENT_H
#define COMPONENT_H


class Component {

public:
	enum Type {
		NONE,
		MESH,
		KEYBOARD_EVENTS,
	};

    Component();
    virtual ~Component()= default;
	virtual int getType();

};

#endif // COMPONENT_H
