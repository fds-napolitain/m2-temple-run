#ifndef CAMERA_H
#define CAMERA_H

#include "entity.h"

class Camera : Entity
{
public:
    Camera(const std::string& name):
     Entity(name)
    {}
};

#endif // CAMERA_H
