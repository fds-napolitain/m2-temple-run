#include "mesh.hpp"

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


    m_vertexArr = new VertexData[vertexs.size()];
    m_indicesArr = new unsigned short[indices.size()*3];

    m_vertex.resize(vertexs.size()); // resize set all values to 0 (use index)
    m_indices.reserve(indices.size()*3); //reserve only allocate memory (use pushback)
    for(unsigned int i = 0; i < vertexs.size(); i++){
        VertexData temp = {vertexs[i], QVector2D()};
        m_vertex[i]     = temp;
        m_vertexArr[i]  = temp;

    }

    unsigned int i = 0;
    for(auto& a : indices)
    {

        m_indices.push_back(a[0]);
        m_indices.push_back(a[1]);
        m_indices.push_back(a[2]);
        m_indicesArr[i++] = a[0];
        m_indicesArr[i++] = a[1];
        m_indicesArr[i++] = a[2];
    }
    std::cout << "succesfully loaded models" << std::endl;
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

    m_vertexArr = new VertexData[vertexNumber];
    m_indicesArr = new unsigned short[indexCount];

    VertextoArray(m_vertexArr, m_vertex);
    IndextoArray(m_indicesArr, m_indices);
}

VertexData* Mesh::VertextoArray(VertexData* arr, std::vector<VertexData> &vertex){

    for(unsigned int i  =0; i< vertex.size(); i++){
        arr[i].position = vertex[i].position;
        arr[i].texture = vertex[i].texture;
    }
    return arr;
}


unsigned short* Mesh::IndextoArray(unsigned short* arr, std::vector<unsigned short>& indices){

    for(unsigned int i =0; i< indices.size(); i++){
        arr[i] = indices[i];
    }
    return arr;
}


void Mesh::draw(GeometryEngine* gEngine, QOpenGLShaderProgram& shaderProgram, int format)
{
    gEngine->drawGeometry(&shaderProgram, m_vertexArr, m_indicesArr, m_vertex.size(), m_indices.size(), format);
}



