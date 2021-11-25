#include "scene.h"

Scene::Scene()
{

}

Scene::~Scene()
{
    delete m_physics;
}

void Scene::draw(GeometryEngine* gEngine, QOpenGLShaderProgram& shaderProgram)
{
    for(auto& entity : m_drawnEntities){
        for(auto& component : entity->getComponents())
        {
            shaderProgram.setUniformValue("transform", entity->getTransform().matrix);
            Mesh* mesh = dynamic_cast<Mesh*>(component);
            if(mesh != nullptr){
                mesh->draw(gEngine, shaderProgram, GL_POINTS);
            }
        }


    }
}
