#include <QApplication>
#include <iostream>

#include "planet.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    if (!QGLFormat::hasOpenGL()) {
//        std::cerr << "This system has no OpenGL support" << std::endl;
//        return 1;
//    }

    Planet* planet = new Planet();
    planet->show();
    std::cout << "oioi\n";

    return app.exec();
}

