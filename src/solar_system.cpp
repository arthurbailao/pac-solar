#include "solar_system.hpp"

#include <GL/glut.h>

SolarSystem::SolarSystem(QWidget *parent)
    : QGLWidget(parent)
    , obj(gluNewQuadric())
    , textures()
    , planets()
{
//    this->setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));

}

void SolarSystem::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    this->loadTextures();
    this->makeObjects();
}


void SolarSystem::resizeGL(int width, int height)
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

void SolarSystem::paintGL()
{
    glDrawBuffer(GL_BACK);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->draw();
}

void SolarSystem::draw()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0, 0, -1.6);
    glRotated(-90, 1, 0, 0);
    glCallList(this->planets[0]);
}

void SolarSystem::makeObjects()
{
    this->planets[0] = glGenLists(1);
    glNewList(this->planets[0], GL_COMPILE);
    gluQuadricTexture(this->obj, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->textures[0]);
    gluSphere(this->obj, 0.127, 50, 50);
    glDisable(GL_TEXTURE_2D);
    glEndList();

}

void SolarSystem::loadTextures()
{
    //Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    this->textures[0] = this->bindTexture(QPixmap(QString("/home/arthurbailao/projects/solar/terra.bmp")), GL_TEXTURE_2D);
}
