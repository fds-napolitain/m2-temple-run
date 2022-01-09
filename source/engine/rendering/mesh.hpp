#ifndef MESH_H
#define MESH_H

#include <vector>
#include <QVector3D>
#include <QVector2D>
#include <QOpenGLTexture>
#include "BasicIO.hpp"
#include "component.hpp"
#include "geometryengine.hpp"
#include "../transform.hpp"



class Mesh : public Component
{
public:


	enum {
		OFFIO,
		OBJIO
	};

    enum Type{
        DEFAULT,
        LIGHT,
    };

    Mesh(int primitive = 0, QVector3D color =  QVector3D(1.0,1.0,1.0));
    ~Mesh() override;
    explicit Mesh(const std::string& path, int format = 0, int primitive = 0, QVector3D color =  QVector3D(1.0,1.0,1.0));
    Mesh(const std::string& path, const QString& texturePath, int format = 0, int primitive = 0, QVector3D color =  QVector3D(1.0,1.0,1.0));
    void loadMesh(const std::string& path, int format);

	void loadTexture(const  QString& texturePath,
                            QOpenGLTexture::Filter minFilter = QOpenGLTexture::Linear,
                            QOpenGLTexture::Filter maxFilter = QOpenGLTexture::Linear,
                            QOpenGLTexture::WrapMode warp = QOpenGLTexture::Repeat
                    );

    void loadTextureHM(const QString& texturePathTexture,
                        const QString& texturePathGround,
                        const QString& texturePathMid,
                        const QString& texturePathHigh, 
                        QOpenGLTexture::Filter minFilter = QOpenGLTexture::Linear, 
                        QOpenGLTexture::Filter maxFilter = QOpenGLTexture::Linear, 
                        QOpenGLTexture::WrapMode warp = QOpenGLTexture::Repeat);

    void initPlaneGeometry(int nH, int nW, int boardSizeX, int boardSizeY);
	void initCubeGeometry();
	[[nodiscard]] std::vector<VertexData> getVertices() const {return m_vertex;}
    [[nodiscard]] std::vector<unsigned short> getIndices() const {return m_indices;}
    void draw(GeometryEngine* gEngine, QOpenGLShaderProgram& shaderProgram, int format);
	[[nodiscard]] int getPrimitive() const {return m_primitive;}
	[[nodiscard]] Type getType() const {return m_type;}
    void setType(Type type) {m_type = type;}
    static unsigned short* indextoArray(unsigned short* arr, std::vector<unsigned short> &indices);
    static VertexData* vertextoArray(VertexData* arr, std::vector<VertexData> &vertex);
    void computeNormals(bool stripe);

    QOpenGLTexture* m_HMground = nullptr;
    QOpenGLTexture* m_HMmid = nullptr;
    QOpenGLTexture* m_HMhigh = nullptr;


private:
    int m_primitive;
    std::vector<VertexData> m_vertex;
    std::vector<unsigned short> m_indices;
	std::vector<QVector3D> m_normals;
    VertexData* m_vertexArr;
    unsigned short* m_indicesArr;
    QVector3D m_color;
    Type m_type;
	QOpenGLTexture* m_texture = nullptr;

};

#endif // MESH_H
