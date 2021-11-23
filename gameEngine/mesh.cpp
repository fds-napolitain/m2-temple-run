#include "mesh.h"

Mesh::Mesh(const std::string& path, int format)
{
    this->loadMesh(path, format);
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
    m_indices.resize(indices.size()*3);
    for(unsigned int i = 0; i < vertexs.size(); i++){
        m_vertex[i].position = vertexs[i];
        m_vertex[i].texture = QVector2D();

    }

    for(unsigned int i = 0; i < indices.size(); i+=3){
       m_indices[i]   = indices[i][0];
       m_indices[i+1] = indices[i+1][1];
       m_indices[i+2] = indices[i+2][2];
   }

}


void Mesh::initPlaneGeometry(int nH, int nW, int boardSizeX, int boardSizeY){
    float plan_xmax = boardSizeX;
    float plan_xmin = -boardSizeX;
    float plan_ymax = boardSizeY;
    float plan_ymin = -boardSizeY;
    float tex_xStep=2/(float)(nW-1);
    float tex_yStep=2/(float)(nH-1);

    float xStep=(plan_xmax-plan_xmin)/(float)(nW-1);
    float yStep=(plan_ymax-plan_ymin)/(float)(nH-1);

//########################################################### PLANE HEIGHT MAP #######################################""

    unsigned int vertexNumber = nH*nW;
    m_vertex.reserve(vertexNumber);
    for(int i=0; i<nH; i++){
         for(int j=0;j<nW; j++){
             m_vertex.push_back( {QVector3D(
                                    plan_xmin + xStep * i,
                                    plan_ymin + yStep * j,
                                    0.0),
                             QVector2D(
                                    (tex_xStep*i)/2,
                                    (tex_yStep*j)/2
                                     )
                            });

        }
    }




    unsigned int indexCount = nW*(nH-1)*2 + 2*(nH-1);
    m_indices.reserve(indexCount);
    for(int i=0; i<nH-1; i++){
         for(int j=0;j<nW; j++){
             //stripe
                 m_indices.push_back(i*nH+j);
                 m_indices.push_back((i+1)*nH+j);

             }
            //end line stripe
             m_indices.push_back((i+1)*nH+nH-1);
             m_indices.push_back((i+1)*nH);
         }

}

VertexData* Mesh::VertextoArray(VertexData* arr, std::vector<VertexData> &tempV){

    for(unsigned int i  =0; i<this->m_vertex.size(); i++){
        arr[i].position = tempV[i].position;
        arr[i].texture = tempV[i].texture;
    }
    return arr;
}


unsigned short* Mesh::IndextoArray(unsigned short* arr){

    for(unsigned int i =0; i<this->m_indices.size(); i++){
        arr[i] = this->m_indices[i];
    }
    return arr;
}


void Mesh::draw(GeometryEngine* gEngine, QOpenGLShaderProgram& shaderProgram)
{
    VertexData v[m_vertex.size()];
    unsigned short arr[m_indices.size()];


    gEngine->drawGeometry(&shaderProgram, m_vertex, m_indices, m_vertex.size(), m_indices.size(), GL_TRIANGLES);
}



