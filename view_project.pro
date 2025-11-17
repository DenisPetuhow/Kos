#-------------------------------------------------
#
# Project created by QtCreator 2023-05-30T10:04:44
#
#-------------------------------------------------

QT       += core gui
QT += core
QT += gui
QT += xml
QT += sql
QT += svg
QT += opengl
QT += concurrent
QT += printsupport
QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = view_project
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += debug_and_release \
   build_all
CONFIG(debug,debug|release) {
       DEBUG_SFX = d
    } else {
        DEBUG_SFX =
    }

QWT_PATH =C:/qwt-6.1.3
QWT_INC_PATH = $${QWT_PATH}/src
QWT_VER = 6.1.3
QWT_LIB = qwt$${DEBUG_SFX}
INCLUDEPATH += $${QWT_INC_PATH}
LIBS += -L$${QWT_PATH}/lib -l$${QWT_LIB}

INCLUDEPATH += ./QMapControl
DEPENDPATH += $$PWD/QMapControl
LIBS += -L./QMapControl/lib -lqmapcontrol$${DEBUG_SFX}1

CONFIG += c++11
INCLUDEPATH += C:/Trolltech/msys64/mingw64/include


LIBS += -LC:/Trolltech/msys64/mingw64/bin -losg$${DEBUG_SFX} -lOpenThreads$${DEBUG_SFX} -losgDB$${DEBUG_SFX} -losgFX$${DEBUG_SFX} -losgGA$${DEBUG_SFX} \
     -losgQt5$${DEBUG_SFX} -losgViewer$${DEBUG_SFX} -losgWidget$${DEBUG_SFX} -losgSim$${DEBUG_SFX} -losgText$${DEBUG_SFX} -losgUtil$${DEBUG_SFX} -losgTerrain$${DEBUG_SFX}
LIBS += -lopengl32
LIBS += -lglu32
LIBS += -lgdi32
LIBS += -LC:/Trolltech/msys64/mingw64/bin -losgEarth$${DEBUG_SFX} -losgEarthUtil$${DEBUG_SFX} -losgEarthFeatures$${DEBUG_SFX} -losgEarthAnnotation$${DEBUG_SFX} -losgEarthSymbology$${DEBUG_SFX}
LIBS += -L C:/msys64/mingw64/lib \
-lgsl
SOURCES += \
        ASD/neworbobj.cpp \
        ASD/neworbsys.cpp \
        ASD/objfileparser.cpp \
        ASD/asdcoordconvertor.cpp \
        ASD/orbitalmotion.cpp \
        ASD/noradsdp4.cpp \
        ASD/noradsgp4.cpp \
        ASD/keplereq.cpp \
        ASD/noradeq.cpp \
        ASD/difeq.cpp \
        ASD/orbitalvehicle.cpp \
        ASD/clipper.cpp \
        ASD/SunPosition.cpp \
        ASD/asddatum.cpp \
        calc_bpla_plan.cpp \
        gui3D/add_bpla.cpp \
        gui3D/scene3d.cpp \
        gui3D/osgviewerQt.cpp \
        gui3D/EarthManip.cpp \
        gui3D/orbitveh3d.cpp \
        gui3D/addorbit.cpp \
        gui3D/addpyramid.cpp \
        gui3D/vizibility.cpp \
        gui3D/addpointearth.cpp \
        ASD/geotask.cpp \
        ASD/interlocation.cpp \
        gui3D/addcone.cpp \
        gui3D/adddostup.cpp \
        main.cpp \
        mainwindow.cpp \
        mathtools/asdfunc.cpp \
        mathtools/asdmatrix3x3.cpp \
        mathtools/asdopticfunc.cpp \
        mathtools/asdrungekutta4.cpp \
        mathtools/asdspline.cpp \
        mathtools/darr.cpp \
        mathtools/gltfunc.cpp \
        orbinput.cpp \
        formscene.cpp \
        paint3d.cpp \
        progressbar.cpp \
        plotgistogram.cpp


HEADERS += \
    ASD/asdtype.h \
    ASD/neworbobj.h \
    ASD/neworbsys.h \
    ASD/objfileparser.h \
    ASD/asdcoordconvertor.h \
    ASD/orbitalmotion.h \
    ASD/noradtype.h \
    ASD/noradsdp4.h \
    ASD/noradsgp4.h \
    ASD/keplereq.h \
    ASD/noradeq.h \
    ASD/difeq.h \
    ASD/orbitalvehicle.h \
    ASD/clipper.hpp \
    ASD/SunPosition.hpp \
    ASD/asddatum.h \
    calc_bpla_plan.h \
    gui3D/add_bpla.h \
    gui3D/scene3d.h \
    gui3D/object3d.h \
    gui3D/osgviewerQt.h \
    gui3D/EarthManip.h \
    gui3D/orbitveh3d.h \
    gui3D/addorbit.h \
    gui3D/addpyramid.h \
    gui3D/vizibility.h \
    gui3D/addpointearth.h \
    ASD/geotask.h \
    gui3D/addcone.h \
    ASD/interlocation.h \
    mainwindow.h \
    mathtools/asdfunc.h \
    mathtools/asdmatrix3x3.h \
    mathtools/asdopticfunc.h \
    mathtools/asdrungekutta4.h \
    mathtools/asdspline.h \
    mathtools/darr.h \
    mathtools/gltfunc.h \
    gui3D/adddostup.h \
        orbinput.h \
        formscene.h \
        paint3d.h \
    progressbar.h \
    plotgistogram.h




FORMS += \
        mainwindow.ui \
        orbinput.ui \
        formscene.ui





# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    common.qrc
#common.qrc

