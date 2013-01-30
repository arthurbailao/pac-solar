#ifndef SOLARSYSTEM_HPP
#define SOLARSYSTEM_HPP

#include <QGLWidget>
#include <GL/glu.h>

class SolarSystem : public QGLWidget
{
    Q_OBJECT

    enum Planets {
        Mercury = 1,
        Venus = 2,
        Earth = 3,
        Mars = 4,
        Jupiter = 5,
        Saturn = 6,
        Uranus = 7,
        Neptune = 8
    };

public:
    explicit SolarSystem(QWidget *parent = 0);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private:
    void draw();
    void makeObjects();
    void loadTextures();

    GLUquadricObj *obj;
    GLuint textures[1];
    GLuint planets[1];


};

#endif // SOLARSYSTEM_HPP
