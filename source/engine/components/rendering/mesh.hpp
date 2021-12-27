#ifndef MESH_H
#define MESH_H

#include <vector>
#include <QVector3D>
#include <QVector2D>
#include <QOpenGLTexture>
#include "source/engine/rendering/BasicIO.hpp"
#include "source/engine/components/component.hpp"
#include "source/engine/transform.hpp"
#include "source/engine/rendering/geometryengine.hpp"

class Mesh : public Component
{

public:
	enum {
		OFFIO,
		OBJIO
	};

    enum Kind {
        DEFAULT,
        LIGHT,
    };

	// au propre faudrait que tout soit attribut je pense
	static void setEngine(GeometryEngine* engine, QOpenGLShaderProgram* shaderProgram, QOpenGLShaderProgram* lightProgram);
	static GeometryEngine* m_engine;
	static QOpenGLShaderProgram* m_shaderProgram;
	static QOpenGLShaderProgram* m_lightProgram;

    explicit Mesh(int primitive = 0, QVector3D color =  QVector3D(1.0,1.0,1.0));
    explicit Mesh(const std::string& path, int format = 0, int primitive = 0, QVector3D color =  QVector3D(1.0,1.0,1.0));
	Mesh(const std::string& path, const QString& texturePath, int format = 0, int primitive = 0, QVector3D color =  QVector3D(1.0,1.0,1.0));
	~Mesh() override;
	int getType() override;

    void loadMesh(const std::string& path, int format);

	void loadTexture(const  QString& texturePath,
                            QOpenGLTexture::Filter minFilter = QOpenGLTexture::Linear,
                            QOpenGLTexture::Filter maxFilter = QOpenGLTexture::Linear,
                            QOpenGLTexture::WrapMode warp = QOpenGLTexture::Repeat
                    );
	void initPlaneGeometry(int nH, int nW, int boardSizeX, int boardSizeY);
	void initCubeGeometry();
	[[nodiscard]] std::vector<VertexData> getVertices() const;
	[[nodiscard]] std::vector<unsigned short> getIndices() const;
	void draw();
	[[nodiscard]] int getPrimitive() const;
	[[nodiscard]] Kind getKind() const;
	void setKind(Kind type);
	static unsigned short* indextoArray(unsigned short* arr, std::vector<unsigned short> &indices);
	static VertexData* vertextoArray(VertexData* arr, std::vector<VertexData> &vertex);
    void computeNormals(bool stripe);


private:
	int m_format;
    int m_primitive;
    std::vector<VertexData> m_vertex;
    std::vector<unsigned short> m_indices;
	std::vector<QVector3D> m_normals;
    VertexData* m_vertexArr;
    unsigned short* m_indicesArr;
    QVector3D m_color;
    Kind m_kind;
	QOpenGLTexture* m_texture = nullptr;

};

#endif // MESH_H
