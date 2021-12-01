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

    Mesh(int primitive = 0) : m_primitive(primitive){}
    ~Mesh() override
    {
        delete m_vertexArr;
        delete m_indicesArr;
    }

    explicit Mesh(const std::string& path, int format = 0, int primitive = 0);
    enum{
        OFFIO,
        OBJIO
     };

    void loadMesh(const std::string& path, int format);
    void initPlaneGeometry(int nH, int nW, int boardSizeX, int boardSizeY);

    [[nodiscard]] inline std::vector<VertexData> getVertices() const {return m_vertex;}

    [[nodiscard]] inline std::vector<unsigned short> getIndices() const {return m_indices;}
    void draw(GeometryEngine* gEngine, QOpenGLShaderProgram& shaderProgram, int format);
    inline int getPrimitive() const {return m_primitive;}

   static unsigned short* indextoArray(unsigned short* arr, std::vector<unsigned short> &indices);
   static VertexData* vertextoArray(VertexData* arr, std::vector<VertexData> &vertex);

private:
    int m_primitive;
    std::vector<VertexData> m_vertex;
    std::vector<unsigned short> m_indices;
    VertexData* m_vertexArr;
    unsigned short* m_indicesArr;
};

#endif // MESH_H
