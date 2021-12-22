#include "scene.hpp"
#include "Light.hpp"

Scene::Scene()
{

}

Scene::~Scene()
{
	delete m_physics;
}

void Scene::draw(GeometryEngine* gEngine, QOpenGLShaderProgram& shaderProgram, QOpenGLShaderProgram& lightProgram)
{
    for(auto entity : m_drawnEntities){

        Light* lightEntity = dynamic_cast<Light*>(entity);
        if(lightEntity != nullptr)
        {
            for(auto& component : entity->getComponents())
            {
                Mesh* mesh = dynamic_cast<Mesh*>(component);
                if(mesh != nullptr){
                    lightProgram.bind();
                    lightProgram.setUniformValue("transform", entity->getTransform()->matrix);
                    mesh->draw(gEngine, lightProgram, mesh->getPrimitive());
                }
            }
        }
        else
        {
            for(auto& component : entity->getComponents())
            {

                Mesh* mesh = dynamic_cast<Mesh*>(component);
                if(mesh != nullptr){
                    shaderProgram.bind();
                    shaderProgram.setUniformValue("transform", entity->getTransform()->matrix);
                    mesh->draw(gEngine, shaderProgram, mesh->getPrimitive());
                }
            }
        }



	}
}
