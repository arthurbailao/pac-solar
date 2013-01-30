#ifndef SOLARSYSTEM_HPP
#define SOLARSYSTEM_HPP

#include <QGLWidget>
#include <QTimer>
#include <GL/glu.h>

class SolarSystem : public QGLWidget
{
    Q_OBJECT

public:
    explicit SolarSystem(QWidget *parent = 0);

    enum Objects {
        Mercury = 0,
        Venus = 1,
        Earth = 2,
        Mars = 3,
        Jupiter = 4,
        Saturn = 5,
        Uranus = 6,
        Neptune = 7,
        Sun = 8,
        Moon = 9
    };

public slots:
    void showObject(Objects obj);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private:
    void draw();
    void makeObjects();
    void loadTextures();
    void light (float r, float g, float b);

    GLUquadricObj *obj;
    GLuint textures[10];
    GLuint objects[10];
    Objects current;
    QTimer timer;

};

#endif // SOLARSYSTEM_HPP
