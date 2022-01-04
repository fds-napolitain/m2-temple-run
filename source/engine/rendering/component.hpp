#ifndef COMPONENT_H
#define COMPONENT_H


class Component {

public:
    Component();
    virtual ~Component()= default;;
    virtual int getCType();

};

enum CType {
	NONE,
	COLLIDER,
	ANIMATION,
};

#endif // COMPONENT_H
