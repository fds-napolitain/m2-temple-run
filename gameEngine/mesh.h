#ifndef MESH_H
#define MESH_H

#include <vector>
#include <QVector3D>
#include <QVector2D>
#include <BasicIO.hpp>
#include "component.h"
#include "geometryengine.h"




class Mesh : public Component
{
public:
    Mesh(){}
    Mesh(const std::string& path, int format = 0);
    enum{
        OFFIO,
        OBJIO
     };

    void loadMesh(const std::string& path, int format);
    void initPlaneGeometry(int nH, int nW, int boardSizeX, int boardSizeY);

    inline const std::vector<VertexData> getVertices() const {return m_vertex;}

    inline const std::vector<unsigned short> getIndices() const {return m_indices;}
    void draw(GeometryEngine* gEngine, QOpenGLShaderProgram& shaderProgram);

   unsigned short* IndextoArray(unsigned short* arr);
   VertexData* VertextoArray(VertexData* arr, std::vector<VertexData> &tempV);

private:
    std::vector<VertexData> m_vertex;
    std::vector<unsigned short> m_indices;
};

#endif // MESH_H
