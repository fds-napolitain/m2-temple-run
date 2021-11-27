#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "physicobject.hpp"
#include <vector>
#include "BoundingSphere.hpp"

class PhysicsEngine
{
public:
    PhysicsEngine();

    void addObject(const PhysicObject& object);
    void simulate(float delta);

    void handleCollisions();

    inline PhysicObject& getObject(unsigned int index){
        return m_objects[index];
    }

    inline unsigned int getNumObjs(){
        return (unsigned int) m_objects.size();
    }
private:
    std::vector<PhysicObject> m_objects;

};

#endif // PHYSICSENGINE_H
