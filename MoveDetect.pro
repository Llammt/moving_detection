TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    tiledetect.cpp \
    checkparameters.cpp

HEADERS += \
    tiledetect.h \
    checkparameters.h

INCLUDEPATH += "C:/Program Files/openCV/opencv/build/install/include"
LIBS += -L"C:/Program Files/openCV/opencv/build/bin" \
        -lopencv_core2412d \
        -lopencv_highgui2412d \
        -lopencv_imgproc2412d \
        -lopencv_calib3d2412d
