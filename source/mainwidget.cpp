/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** collider written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwidget.hpp"


MainWidget::MainWidget(QWidget *parent) :
		QOpenGLWidget(parent),
		geometries(nullptr),
		angularSpeed(0)

{
    //initSphereGeometry(this->sphere);
}


MainWidget::MainWidget(TargetFPS fps, QWidget *parent) : QOpenGLWidget(parent),
														 geometries(nullptr),
														 angularSpeed(0)
{
	this->fps = fps;
}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the grass
    // and the buffers.
    makeCurrent();
    delete geometries;
    delete scene;
    doneCurrent();
}

//! [0]
/**
 * Appuis souris
 * @param e
 */
void MainWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

/**
 * Relachement de souris
 * @param e
 */
void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}
//! [0]

//! [1]
void MainWidget::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation ;

		//update();
    }
}
//! [1]

void MainWidget::keyPressEvent(QKeyEvent *event)
{
	SceneGraph* sceneGraph = (SceneGraph*) scene;
	Transform* transform = sceneGraph->mainDecor->getTransform();

    if (!sceneGraph->isMovingLeft && !sceneGraph->isMovingRight && !sceneGraph->player->isJumping && !sceneGraph->player->hasJumped) //si le joueur ne se d�place pas, regarde sur quelle touche il appuie.
    {
        switch (event->key()) {
                case Qt::Key_Z: /* haut */
                    projection.translate(QVector3D(0.0, 0.0, 10.0) * timeStep);
                    break;
                case Qt::Key_Q: /* gauche */;
                    projection.translate(QVector3D(10.0, 0.0, 0.0) * timeStep);
                    break;
                case Qt::Key_D: /*droite */
                    projection.translate(QVector3D(-10.0, 0.0, 0.0) * timeStep);
                  break;
                case Qt::Key_S: /* bas */
                    projection.translate(QVector3D(0.0,0.0, -10.0) * timeStep);
                    break;
                case Qt::Key_A: /* descendre */
                    projection.translate(QVector3D(0.0, 0.0, -50.0) * timeStep);;
                    break;
                case Qt::Key_E: /* monter */
                    projection.translate(QVector3D(0.0, 0.0, 50.0) * timeStep);
                    break;
                case Qt::Key_R: /* tricher ! (regagner un pdv, pour la d�mo) */
                    if (sceneGraph->player->PointDeVie < 3)
                    {
                        sceneGraph->player->PointDeVie += 1;
                    }
                    break;
                case Qt::Key_X: /* pause */
                    if (sceneGraph->tempSpeed == 0.0f)
                    {
                        sceneGraph->tempSpeed = sceneGraph->scrollingSpeed;
                        sceneGraph->scrollingSpeed = 0.0f;
                    }
                    else
                    {
                        sceneGraph->scrollingSpeed = sceneGraph->tempSpeed;
                        sceneGraph->tempSpeed = 0.0f;
                    }
                    break;
		        case Qt::Key_Left:
                    if (!sceneGraph->joueur_rl)
                    {
                        sceneGraph->isMovingLeft = true;
                        sceneGraph->isMovingRight = false;
                    }
			        break;
		        case Qt::Key_Right:

                    if (!sceneGraph->joueur_rr)
                    {
                        sceneGraph->isMovingLeft = false;
                        sceneGraph->isMovingRight = true;
                    }

			        break;
                case Qt::Key_Space:

                    sceneGraph->player->isJumping = true;
                    sceneGraph->isJumping = true;
                    break;
                case Qt::Key_Up:
                    sceneGraph->player->isJumping = true;
                    sceneGraph->isJumping = true;
                    break;

        }
	
    }
    //projection.translate(0.0, 0.0, -1.0) ;
      //update();

    // Save mouse press position
  //  mousePressPosition = QVector2D(e->localPos());
}

/**
 * Initialiation des fonctions OpenGL
 */
void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();


//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);
//! [2]



   // geometries = new GeometryEngine;

    currentTime.start();
    initScene();

    // Use QBasicTimer because its faster than QTimer
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(doUpdate()));
	timer->start(fps.getTimePerFrame());
}

//! [3]
/**
 * Initialisations des shaders (*.glsl)
 */
void MainWidget::initShaders()
{
	// Compile vertex shader
	if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
		close();

	// Compile fragment shader
	if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
		close();

	// Link shader pipeline
	if (!program.link())
		close();

	// Bind shader pipeline for use
	if (!program.bind())
		close();



    // Compile vertex shader
    if (!lightProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vlight.glsl"))
        close();

    // Compile fragment shader
    if (!lightProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/flight.glsl"))
        close();

    // Link shader pipeline
    if (!lightProgram.link())
        close();

    // Compile vertex shader
    if (!HMProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshaderHM.glsl"))
        close();

    // Compile fragment shader
    if (!HMProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshaderHM.glsl"))
        close();

    // Link shader pipeline
    if (!HMProgram.link())
        close();

    // Bind shader pipeline for use
    if (!HMProgram.bind())
        close();




}
//! [3]

//! [5]
/**
 * Fenetre opengl
 * @param w
 * @param h
 */
void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 1.0, zFar = 500.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}
//! [5]

/**
 * Initialisation scene
 */
void MainWidget::initScene()
{
     scene = new SceneGraph(new Entity("World"));
     geometries = new GeometryEngine();
}

/**
 * Boucle d'affichage OpenGL
 */
void MainWidget::paintGL()
{
    timeStep = currentTime.nsecsElapsed() * 0.000000001;
  //  std::cout << "fps: " << floor(1/ timeStep) << " interval: " << fps.getSwapInterval() << " ms: " << fps.getTimePerFrame() << std::endl;
    currentTime.restart();


    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*
    grass->bind(0);
    heightmap->bind(1);
    rock->bind(2);
    snow->bind(3);*/

//! [6]
    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -10.0);
    matrix.rotate(rotation);
    lightProgram.bind();
    lightProgram.setUniformValue("cam_pos", QVector3D(matrix(0,3), matrix(1,3), matrix(2,3)));

    // Set modelview-projection matrix
//! [6]
//!
//!
//! ../TP3/Qt_solar/sphere.obj


    // Use grass unit 0 which contains cube.png
   // SceneGraph* sg = (SceneGraph*) scene;
    //std::vector<Component> t =  sg->getRoot()->getComponents();
  //  Mesh* g = dynamic_cast<Mesh*>(&t[0]);
  // std::cout << g->getIndices().size() << " "  << g->getVertices().size() << std::endl;

   //gScene->update()
    

    
    program.bind();
    program.setUniformValue("texture", 3);
    program.setUniformValue("mvp_matrix", projection * matrix);
    HMProgram.bind();   
    HMProgram.setUniformValue("texture", 3);
    HMProgram.setUniformValue("mvp_matrix", projection * matrix);
    HMProgram.setUniformValue("groundH", 0);
    HMProgram.setUniformValue("midH", 1);
    HMProgram.setUniformValue("topH", 2);
    lightProgram.bind();
    lightProgram.setUniformValue("mvp_matrix", projection * matrix);
    scene->draw(geometries, program, lightProgram,HMProgram);
    scene->update(timeStep);
    // Draw cube geometry
	timer->start(fps.getTimePerFrame());
}

/**
 * slot action: update tous les 60 FPS
 */
void MainWidget::doUpdate() {
	update();
}
