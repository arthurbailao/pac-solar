#include <QApplication>
#include <iostream>

#include "solar_system.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    if (!QGLFormat::hasOpenGL()) {
//        std::cerr << "This system has no OpenGL support" << std::endl;
//        return 1;
//    }

    SolarSystem* planet = new SolarSystem();
    planet->show();
    planet->showObject(SolarSystem::Earth);

    return app.exec();
}

