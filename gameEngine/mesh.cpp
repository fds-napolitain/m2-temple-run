#include "mesh.h"

Mesh::Mesh(const std::string& path, int format)
{
    loadMesh(path, format);
}

void Mesh::loadMesh(const std::string &path, int format){
    std::vector<QVector3D> vertexs;
    std::vector<std::vector<unsigned int>> indices;
    switch(format){
        case OFFIO:
            OFFIO::open(path, vertexs, indices);
            break;
        case OBJIO:
            OBJIO::open(path, vertexs, indices);
            break;
    }


    m_vertex.resize(vertexs.size());
    m_indices.resize(indices.size());
    unsigned int i =0;
    for(auto& vertex: vertexs){
        m_vertex[i].position = vertex;
        m_vertex[i].texture = QVector2D();
        i++;
    }

    i=0;
    for(auto& index : indices){

        m_indices[i++] = index[0];
        m_indices[i++] = index[1];
        m_indices[i++] = index[2];

    }


}


