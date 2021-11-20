#ifndef COMPONENT_H
#define COMPONENT_H

#include "iostream"

class Component
{
public:    
    std::string name;
    
    Component();
    virtual ~Component();
};

#endif // COMPONENT_H
