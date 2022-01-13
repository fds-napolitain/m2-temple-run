#include "scene.hpp"
#include "source/engine/entity/Light.hpp"

/**
 * Constructeur (par défaut)
 */
Scene::Scene() {

}

/**
 * Destructeur
 */
Scene::~Scene() {
	delete m_physics;
}

/**
 * Dessine le graphe de scene
 * @param gEngine
 * @param shaderProgram
 * @param lightProgram
 */
void Scene::draw(GeometryEngine* gEngine, QOpenGLShaderProgram& shaderProgram, QOpenGLShaderProgram& lightProgram, QOpenGLShaderProgram& HMProgram)
{
    for (auto entity : m_drawnEntities)
    {
        if (entity->getEType() == EntityType::LIGHT)
        { // light
            Light* lightEntity = dynamic_cast<Light*>(entity);
            for (auto& component : entity->getComponents()) {
                Mesh* mesh = dynamic_cast<Mesh*>(component);
                if (mesh != nullptr) {
                    lightProgram.bind();
                    lightProgram.setUniformValue("transform", entity->getTransform()->matrix);
                    lightProgram.setUniformValue("light_color", lightEntity->getColor());
                    mesh->draw(gEngine, lightProgram, mesh->getPrimitive());
                    shaderProgram.bind();
                    shaderProgram.setUniformValue("light_color", lightEntity->getColor());
                    shaderProgram.setUniformValue("light_position", lightEntity->getTransform()->getWorldTranslate());

                    HMProgram.bind();
                    HMProgram.setUniformValue("light_color", lightEntity->getColor());
                    HMProgram.setUniformValue("light_position", lightEntity->getTransform()->getWorldTranslate());


                }
            }
        }
        else // normal
        {
            if (entity->getName() == "right" || entity->getName() == "left" || entity->getName() == "fond" || entity->getName() == "staticleft" || entity->getName() == "staticright"  ) // heightmap
            {

                for (auto& component : entity->getComponents())
                {
                    Mesh* mesh = dynamic_cast<Mesh*>(component);
                    if (mesh != nullptr) {

                        HMProgram.bind();
                        HMProgram.setUniformValue("transform", entity->getTransform()->matrix);
                        HMProgram.setUniformValue("normals_rotation", entity->getTransform()->rotate.toRotationMatrix());
                        HMProgram.setUniformValue("groundH", 0);
                        HMProgram.setUniformValue("midH", 1);
                        HMProgram.setUniformValue("topH", 2);
                        mesh->draw(gEngine, HMProgram, mesh->getPrimitive());

                    }
                }
            }
            else // classique
            {
                for (auto& component : entity->getComponents())
                {
                    Mesh* mesh = dynamic_cast<Mesh*>(component);
                    if (mesh != nullptr) {
                        shaderProgram.bind();
                        shaderProgram.setUniformValue("transform", entity->getTransform()->matrix);
                        shaderProgram.setUniformValue("normals_rotation", entity->getTransform()->rotate.toRotationMatrix());
                        mesh->draw(gEngine, shaderProgram, mesh->getPrimitive());
                    }
                }
            }
        }
	}
}
