QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cc \
    View/mazeview.cc \
    Controller/Controller.cc \
    Model/Model.cc \
    Model/Parser.cc \
    Model/PathFinder.cc \
    Model/Generator.cc \
    View/GraphicsScene.cc

HEADERS += \
    View/mazeview.h \
    Controller/Controller.h \
    Model/Model.h \
    Model/Parser.h \
    Model/PathFinder.h \
    Model/Generator.h \
    View/GraphicsScene.h

FORMS += \
    View/mazeview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
