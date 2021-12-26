#include "mesh.hpp"

Mesh::Mesh(int primitive, QVector3D color) :
m_primitive(primitive), m_color(color) {
}

Mesh::Mesh(const std::string& path, int format, int primitive, QVector3D color) :
m_primitive(primitive), m_color(color)
{
    this->loadMesh(path, format);
}

Mesh::Mesh(const std::string &path, const QString &texturePath, int format, int primitive, QVector3D color) :
m_primitive(primitive), m_color(color)
{
	this->loadMesh(path, format);
	loadTexture(texturePath);
}

Mesh::~Mesh() {
	delete m_vertexArr;
	delete m_indicesArr;
}

void Mesh::loadMesh(const std::string &path, int format) {
	this->m_format = format;
    std::vector<QVector3D> vertices;
    std::vector<std::vector<unsigned int>> indices;
    switch (format){
        case OFFIO:
            offio::open(path, vertices, indices);
            break;
        case OBJIO:
            objio::open(path, vertices, indices);
            break;
    }


    m_vertexArr = new VertexData[vertices.size()];
    m_indicesArr = new unsigned short[indices.size()*3];

    m_vertex.resize(vertices.size()); // resize set all values to 0 (use index)
    m_indices.reserve(indices.size()*3); //reserve only allocate memory (use pushback)
    for(unsigned int i = 0; i < vertices.size(); i++){
		VertexData temp;
		if (path == ":/sphere.off") {
			m_normals.push_back(vertices[i] - QVector3D());
            Transform::printV3D(m_normals[i]);
			temp = {vertices[i], QVector2D(asin(m_normals[i].x()) / 3.1415 + 0.5, asin(m_normals[i].y()) / 3.1415 + 0.5), QVector3D(vertices[i] - QVector3D())};
		} else {
			temp = {vertices[i], QVector2D()};
		}
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
                                    plan_ymin + yStep * j,
                                    0.0,
                                    plan_xmin + xStep * i),
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

    vertextoArray(m_vertexArr, m_vertex);
    indextoArray(m_indicesArr, m_indices);
    computeNormals(true);
}


void Mesh::initCubeGeometry() {
	// For cube we would need only 8 vertices but we have to
	// duplicate vertex for each face because texture coordinate
	// is different.
	m_vertexArr = new VertexData[24] {
			// Vertex data for face 0
			{QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)},  // v0
			{QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.0f)}, // v1
			{QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.5f)},  // v2
			{QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v3

			// Vertex data for face 1
			{QVector3D( 1.0f, -1.0f,  1.0f), QVector2D( 0.0f, 0.5f)}, // v4
			{QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.5f)}, // v5
			{QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)},  // v6
			{QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v7

			// Vertex data for face 2
			{QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v8
			{QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.5f)},  // v9
			{QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}, // v10
			{QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)},  // v11

			// Vertex data for face 3
			{QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v12
			{QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f)},  // v13
			{QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v14
			{QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(1.0f, 0.5f)},  // v15

			// Vertex data for face 4
			{QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.0f)}, // v16
			{QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v17
			{QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v18
			{QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v19

			// Vertex data for face 5
			{QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v20
			{QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v21
			{QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v22
			{QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}  // v23
	};

	// Indices for drawing cube faces using triangle strips.
	// Triangle strips can be connected by duplicating indices
	// between the strips. If connecting strips have opposite
	// vertex order then last index of the first strip and first
	// index of the second strip needs to be duplicated. If
	// connecting strips have same vertex order then only last
	// index of the first strip needs to be duplicated.
    int indexCount = 34;
	m_indicesArr = new unsigned short[indexCount] {
			0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
			4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
			8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
			12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
			16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
			20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
	};
	m_vertex.resize(24);
	m_indices.resize(indexCount);
    for(unsigned int i =0; i<indexCount; i++){
        m_indices[i] = m_indicesArr[i];
    }
	computeNormals(true);
//! [1]
}

VertexData* Mesh::vertextoArray(VertexData* arr, std::vector<VertexData> &vertex){

    for(unsigned int i  =0; i< vertex.size(); i++){
        arr[i].position = vertex[i].position;
        arr[i].texture = vertex[i].texture;
    }
    return arr;
}

unsigned short* Mesh::indextoArray(unsigned short* arr, std::vector<unsigned short>& indices){

    for(unsigned int i =0; i< indices.size(); i++){
        arr[i] = indices[i];
    }
    return arr;
}

/**
 * Dessine l'objet
 */
void Mesh::draw() {
	if (m_texture != nullptr) {
		m_texture->bind(3);
	}
	m_engine->drawGeometry(m_program, m_vertexArr, m_indicesArr, m_vertex.size(), m_indices.size(), m_format, m_color);
}

void Mesh::loadTexture(const QString& texturePath, QOpenGLTexture::Filter minFilter, QOpenGLTexture::Filter maxFilter, QOpenGLTexture::WrapMode warp ) {
	m_texture = new QOpenGLTexture(QImage(texturePath).mirrored());
//    m_texture->generateMipMaps();
	m_texture->setMinificationFilter(minFilter);
	m_texture->setMagnificationFilter(maxFilter);
	m_texture->setWrapMode(warp);
}

void Mesh::computeNormals(bool stripe) {
    if (stripe){
        for(unsigned int i = 0; i < m_indices.size(); i += 6){
            QVector3D n0 = QVector3D::crossProduct(m_vertexArr[m_indices[i+1]].position - m_vertexArr[m_indices[i]].position, m_vertexArr[m_indices[i+2]].position - m_vertexArr[m_indices[i]].position );
            QVector3D n1 = QVector3D::crossProduct(m_vertexArr[m_indices[i]].position - m_vertexArr[m_indices[i+1]].position, m_vertexArr[m_indices[i+2]].position - m_vertexArr[m_indices[i+1]].position );
            QVector3D n2 = QVector3D::crossProduct(m_vertexArr[m_indices[i]].position - m_vertexArr[m_indices[i+2]].position, m_vertexArr[m_indices[i+1]].position - m_vertexArr[m_indices[i+2]].position );
            QVector3D n3 = QVector3D::crossProduct(m_vertexArr[m_indices[i+1]].position - m_vertexArr[m_indices[i+3]].position, m_vertexArr[m_indices[i+2]].position - m_vertexArr[m_indices[i+3]].position );
            m_vertexArr[m_indices[i]].normal = n0;
            m_vertexArr[m_indices[i+1]].normal = n1;
            m_vertexArr[m_indices[i+2]].normal = n2;
            m_vertexArr[m_indices[i+3]].normal = n3;
        }
    }
}

/**
 * Renvoit component type == Mesh
 * @return
 */
int Mesh::getType() {
	return Type::MESH;
}

void Mesh::setKind(Mesh::Kind type) {
	m_kind = type;
}

Mesh::Kind Mesh::getKind() const {
	return m_kind;
}

int Mesh::getPrimitive() const {
	return m_primitive;
}

std::vector<unsigned short> Mesh::getIndices() const {
	return m_indices;
}

std::vector<VertexData> Mesh::getVertices() const {
	return m_vertex;
}

/**
 * Initialise geometry engine et QOpenGLShaderProgram à tous les mesh
 * @param engine
 * @param program
 */
void Mesh::setEngine(GeometryEngine *engine, QOpenGLShaderProgram *program) {
	Mesh::m_engine = engine;
	Mesh::m_program = program;
}
