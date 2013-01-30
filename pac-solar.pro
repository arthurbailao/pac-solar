QT += opengl
TEMPLATE = app
TARGET = pac-solar

SOURCES += \
    src/main.cpp \
    src/planet.cpp

HEADERS += \
    src/planet.hpp

unix {
     LIBS += -lGLU -lglut
 }
