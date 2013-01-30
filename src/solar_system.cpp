#include "solar_system.hpp"

#include <QMap>
#include <QString>
#include <qmath.h>
#include <GL/glut.h>

SolarSystem::SolarSystem(QWidget *parent)
    : QGLWidget(parent)
    , obj(gluNewQuadric())
    , textures()
    , objects()
    , current(Objects(-1))
    , timer()
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.setInterval(0);
    timer.start();
}

void SolarSystem::initializeGL()
{
    //Habilita o uso de iluminação
    glEnable(GL_LIGHTING);
    // Habilita a luz de número 0
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

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
    if(this->current < 0)
        return;

    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    QMap<Objects, QPair<GLdouble,GLdouble> > rotationAndTranslation;
    rotationAndTranslation[SolarSystem::Mercury] = qMakePair<GLdouble,GLdouble>(90.0, -1);
    rotationAndTranslation[SolarSystem::Venus] = qMakePair<GLdouble,GLdouble>(-90.0, -1.6);
    rotationAndTranslation[SolarSystem::Earth] = qMakePair<GLdouble,GLdouble>(-90.0, -1.6);
    rotationAndTranslation[SolarSystem::Mars] = qMakePair<GLdouble,GLdouble>(90.0, -1);
    rotationAndTranslation[SolarSystem::Saturn] = qMakePair<GLdouble,GLdouble>(90.0, -5);
    rotationAndTranslation[SolarSystem::Uranus] = qMakePair<GLdouble,GLdouble>(90.0, -3);
    rotationAndTranslation[SolarSystem::Neptune] = qMakePair<GLdouble,GLdouble>(90.0, -3);
    rotationAndTranslation[SolarSystem::Jupiter] = qMakePair<GLdouble,GLdouble>(90.0, -6);
    rotationAndTranslation[SolarSystem::Sun] = qMakePair<GLdouble,GLdouble>(90.0, -15);
    rotationAndTranslation[SolarSystem::Moon] = qMakePair<GLdouble,GLdouble>(90.0, -1.5);

    glTranslated(0, 0, rotationAndTranslation[this->current].second);
    if(this->current == SolarSystem::Saturn) {
        glRotated(27, 1, 0, 0);
        glRotated(10, 0, 0, 1);
    }
    glRotated(rotationAndTranslation[this->current].first, 1, 0, 0);
    glRotated(-20*t, 0, 0, 1);
    glCallList(this->objects[this->current]);
}

void SolarSystem::makeObjects()
{
    //Desenha os planetas
    QMap<Objects, GLdouble> planetsRadius;
    planetsRadius[SolarSystem::Mercury] = 0.048;
    planetsRadius[SolarSystem::Venus] = 0.121;
    planetsRadius[SolarSystem::Earth] = 0.127;
    planetsRadius[SolarSystem::Mars] = 0.068;
    planetsRadius[SolarSystem::Jupiter] = 0.543;
    planetsRadius[SolarSystem::Saturn] = 0.320;
    planetsRadius[SolarSystem::Uranus] = 0.21;
    planetsRadius[SolarSystem::Neptune] = 0.19;

    QMap<Objects, GLdouble>::const_iterator it = planetsRadius.begin();
    for(;it != planetsRadius.end(); ++it) {
        this->objects[it.key()] = glGenLists(it.key());
        glNewList(this->objects[it.key()], GL_COMPILE);
        gluQuadricTexture(this->obj, GL_TRUE);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, this->textures[it.key()]);
        gluSphere(this->obj, it.value(), 50, 50);
        glDisable(GL_TEXTURE_2D);
        if(it.key() == SolarSystem::Saturn) {
            glBegin(GL_LINE_LOOP);
            for (int i = 0; i < 100 + 1; i++) {  // +1 para cerrar
                light(0.86415094, 0.86328125, 0.8515625);
                glVertex2f(0.6 * cos(2.0 * 3.14 * i / 100), 0.6 * sin(2.0 * 3.14 * i / 100) );
                glVertex2f(0.5 * cos(2.0 * 3.14 * i / 100),
                           0.5 * sin(2.0 * 3.14 * i / 100) );
                glColor3f(0.80078125f, 0.6875f, 0.4296875f);
                glVertex2f(0.4 * cos(2.0 * 3.14 * i / 100),
                           0.4 * sin(2.0 * 3.14 * i / 100) );
            }
            glEnd();
        }
        glEndList();
    }

    //Desenha o sol
    this->objects[SolarSystem::Sun] = glGenLists(SolarSystem::Sun);
    glNewList(this->objects[SolarSystem::Sun], GL_COMPILE);
    gluQuadricTexture(this->obj, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->textures[SolarSystem::Sun]);
    gluSphere(this->obj, 1.39, 25, 25);
    glDisable(GL_TEXTURE_2D);
    glEndList();

    //Desenha a lua
    this->objects[SolarSystem::Moon] = glGenLists(SolarSystem::Moon);
    glNewList(this->objects[SolarSystem::Moon], GL_COMPILE);
    gluQuadricTexture(this->obj, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->textures[SolarSystem::Moon]);
    gluSphere(this->obj, 0.02, 50, 50);
    glDisable(GL_TEXTURE_2D);
    glEndList();

}

void SolarSystem::loadTextures()
{
    //Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);

    QMap<Objects, QString> texturesFilenames;
    texturesFilenames[SolarSystem::Mercury] = ":/imgs/mercury.bmp";
    texturesFilenames[SolarSystem::Venus] = ":/imgs/venus.bmp";
    texturesFilenames[SolarSystem::Earth] = ":/imgs/earth.bmp";
    texturesFilenames[SolarSystem::Mars] = ":/imgs/mars.bmp";
    texturesFilenames[SolarSystem::Saturn] = ":/imgs/saturn.bmp";
    texturesFilenames[SolarSystem::Uranus] = ":/imgs/uranus.bmp";
    texturesFilenames[SolarSystem::Neptune] = ":/imgs/neptune.bmp";
    texturesFilenames[SolarSystem::Jupiter] = ":/imgs/jupiter.bmp";
    texturesFilenames[SolarSystem::Sun] = ":/imgs/sun.bmp";
    texturesFilenames[SolarSystem::Moon] = ":/imgs/moon.bmp";

    QMap<Objects, QString>::const_iterator it = texturesFilenames.begin();
    for(; it != texturesFilenames.end(); ++it)
        this->textures[it.key()] = this->bindTexture(QPixmap(it.value()), GL_TEXTURE_2D);
}

void SolarSystem::light(float r, float g, float b)
{
    GLfloat ambientLight[4]={r,g,b,1.0};
    GLfloat specLight[4]={r, g, b, 1.0};// "brilho"
    GLfloat ligthPos[4]={0.0, 0.0, 0.0, 1.0};

    // Capacidade de brilho do material
    GLint material = 10;

    glMateriali(GL_FRONT_AND_BACK,GL_SHININESS, material);

    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    glLightfv(GL_LIGHT0, GL_SPECULAR, specLight );
    glLightfv(GL_LIGHT0, GL_POSITION, ligthPos );

    // Habilita o modelo de colorização de Gouraud
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void SolarSystem::showObject(Objects planet)
{
    this->current = planet;
    this->paintGL();
}
