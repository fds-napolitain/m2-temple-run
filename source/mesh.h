#ifndef MESH_H
#define MESH_H

#include <vector>
#include <QVector3D>
#include <QVector2D>
#include "BasicIO.hpp"
#include "component.h"
#include "geometryengine.h"




class Mesh : public Component
{
public:
    Mesh(){}
    ~Mesh()
    {
        delete m_vertexArr;
        delete m_indicesArr;
    }

    Mesh(const std::string& path, int format = 0);
    enum{
        OFFIO,
        OBJIO
     };

    void loadMesh(const std::string& path, int format);
    void initPlaneGeometry(int nH, int nW, int boardSizeX, int boardSizeY);

    inline const std::vector<VertexData> getVertices() const {return m_vertex;}

    inline const std::vector<unsigned short> getIndices() const {return m_indices;}
    void draw(GeometryEngine* gEngine, QOpenGLShaderProgram& shaderProgram, int format);

   unsigned short* IndextoArray(unsigned short* arr, std::vector<unsigned short> &indices);
   VertexData* VertextoArray(VertexData* arr, std::vector<VertexData> &vertices);

private:
    std::vector<VertexData> m_vertex;
    std::vector<unsigned short> m_indices;
    VertexData* m_vertexArr;
    unsigned short* m_indicesArr;
};

#endif // MESH_H
