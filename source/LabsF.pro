TEMPLATE = app

QT += qml quick widgets declarative
CONFIG += c++14
VPATH += ./source
SOURCES += \
    main.cpp \
    algorithms/branchandboundalgorithmprocessor.cpp \
    algorithms/bruteforcesearchalgorithmprocessor.cpp \
    algorithms/methodprocessor.cpp \
    app/core.cpp \
    salesman/city.cpp
RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    algorithms/branchandboundalgorithmprocessor.h \
    algorithms/bruteforcesearchalgorithmprocessor.h \
    algorithms/methodprocessor.h \
    app/core.h \
    salesman/city.h

