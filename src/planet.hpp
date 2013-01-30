#ifndef PLANET_HPP
#define PLANET_HPP

#include <QGLWidget>

#include <GL/glu.h>

class Planet : public QGLWidget
{
    Q_OBJECT
public:
    explicit Planet(QWidget *parent = 0);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private:
    void draw();

    GLUquadricObj *obj;
    GLuint textures[1];

};

#endif // PLANET_HPP
