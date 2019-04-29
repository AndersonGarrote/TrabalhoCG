QT += core gui opengl

TARGET = polygonal-shading

TEMPLATE = app

SOURCES += main.cpp\
    MainWindow.cpp \
    TrackBall.cpp \
    GLWidget.cpp \
    Camera.cpp \
    Light.cpp \
    Material.cpp

HEADERS  += \
    TrackBall.h \
    MainWindow.h \
    GLWidget.h \
    Camera.h \
    Light.h \
    Material.h

FORMS    += mainwindow.ui

OTHER_FILES += fgouraud.glsl \
    vgouraud.glsl

RESOURCES += \
    resources.qrc
