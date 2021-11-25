#ifndef CAMERA_H
#define CAMERA_H

#include "entity.h"

class Camera : public Entity
{
public:
    Camera(const std::string& name):
     Entity(name)
    {}
};

#endif // CAMERA_H
