QT += opengl webkit
TEMPLATE = app
TARGET = pac-solar

SOURCES += \
    src/main.cpp \
    src/solar_system.cpp \
    src/main_window.cpp

HEADERS += \
    src/solar_system.hpp \
    src/main_window.hpp

unix {
     LIBS += -lGLU -lglut
 }

RESOURCES += \
    textures.qrc

FORMS += \
    src/main_window.ui
