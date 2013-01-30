QT += opengl
TEMPLATE = app
TARGET = pac-solar

SOURCES += \
    src/main.cpp \
    src/solar_system.cpp

HEADERS += \
    src/solar_system.hpp

unix {
     LIBS += -lGLU -lglut
 }
