#include "planet.hpp"

#include <GL/glut.h>

Planet::Planet(QWidget *parent)
    : QGLWidget(parent)
    , obj(NULL)
    , textures()
{
//    this->setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
}

void Planet::initializeGL()
{
    //Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);

        glEnable(GL_DEPTH_TEST);

    this->obj = gluNewQuadric();
    gluQuadricTexture(this->obj,GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    this->textures[0] = this->bindTexture(QPixmap(QString("/home/arthurbailao/projects/solar/terra.bmp")), GL_TEXTURE_2D);
}


void Planet::resizeGL(int width, int height)
{
    if(!height)
        height = 1;

    GLfloat ratio = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(16, ratio, 1, 800);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,80,200, 50,-20,30, 0,1,0);
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void Planet::paintGL()
{
    glDrawBuffer(GL_BACK);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->draw();
}

void Planet::draw()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0, 0, -1.6);
    glRotated(-90, 1, 0, 0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,this->textures[0]);
    gluSphere(this->obj,0.127,50,50);
    glDisable(GL_TEXTURE_2D);
}
