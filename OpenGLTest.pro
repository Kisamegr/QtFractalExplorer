QT += qml quick opengl widgets quickwidgets

CONFIG += c++11
SOURCES += main.cpp \
    mypoint2d.cpp
HEADERS += \
    qopenglitem.h \
    mypoint2d.h \
    openglfractals.h

RESOURCES += qml.qrc

LIBS += opengl32.lib

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

