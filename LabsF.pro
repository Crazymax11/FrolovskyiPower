TEMPLATE = app

QT += qml quick widgets
CONFIG += c++14
SOURCES += main.cpp \
    core.cpp \
    methodprocessor.cpp \
    geneticalgorithmprocessor.cpp \
    antcolonyalgorithmprocessor.cpp \
    bruteforcesearchalgorithmprocessor.cpp \
    dynamicprogrammicalgorithmprocessor.cpp \
    branchandboundalgorithmprocessor.cpp \
    simulatedannealingprocessor.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    core.h \
    methodprocessor.h \
    geneticalgorithmprocessor.h \
    antcolonyalgorithmprocessor.h \
    bruteforcesearchalgorithmprocessor.h \
    dynamicprogrammicalgorithmprocessor.h \
    branchandboundalgorithmprocessor.h \
    simulatedannealingprocessor.h

