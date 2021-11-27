#ifndef MESH_H
#define MESH_H

#include <vector>
#include <QVector3D>
#include <QVector2D>
#include "BasicIO.hpp"
#include "component.hpp"
#include "geometryengine.hpp"




class Mesh : public Component
{
public:
    Mesh(){}
    ~Mesh() override
    {
        delete m_vertexArr;
        delete m_indicesArr;
    }

    explicit Mesh(const std::string& path, int format = 0);
    enum{
        OFFIO,
        OBJIO
     };

    void loadMesh(const std::string& path, int format);
    void initPlaneGeometry(int nH, int nW, int boardSizeX, int boardSizeY);

    [[nodiscard]] inline const std::vector<VertexData> getVertices() const {return m_vertex;}

    [[nodiscard]] inline const std::vector<unsigned short> getIndices() const {return m_indices;}
    void draw(GeometryEngine* gEngine, QOpenGLShaderProgram& shaderProgram, int format);

   static unsigned short* indextoArray(unsigned short* arr, std::vector<unsigned short> &indices);
   static VertexData* vertextoArray(VertexData* arr, std::vector<VertexData> &vertex);

private:
    std::vector<VertexData> m_vertex;
    std::vector<unsigned short> m_indices;
    VertexData* m_vertexArr;
    unsigned short* m_indicesArr;
};

#endif // MESH_H
