#ifndef MESH_H
#define MESH_H

#include <vector>
#include <QVector3D>
#include <QVector2D>
#include <BasicIO.hpp>

struct VertexData
{
    QVector3D position;
    QVector2D texture;
};

class Mesh
{
public:
    Mesh(){}
    Mesh(const std::string& path, int format = 0);
    enum{
        OFFIO,
        OBJIO
     };

    void loadMesh(const std::string& path, int format);



private:
    std::vector<VertexData> m_vertex;
    std::vector<unsigned short> m_indices;
};

#endif // MESH_H
