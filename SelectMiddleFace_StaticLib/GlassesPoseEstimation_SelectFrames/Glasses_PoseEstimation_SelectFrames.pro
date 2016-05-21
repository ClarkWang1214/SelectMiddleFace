TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11


TEMPLATE = lib
CONFIG += staticlib
CONFIG += release
unix {
    target.path = /usr/lib
    INSTALLS += target
}

DESTDIR = ../../bin

SOURCES += \
    ../src/selectFrames.cpp

HEADERS += \
    ../src/FaceAR/pre_main.h \
    ../src/selectFrames.h

INCLUDEPATH +=  \
                ..\
                ../Thirdparty \
                ../Thirdparty/glew \
                ../Thirdparty/glm \
                ../Thirdparty/cereal-1.1.1 \
                ../src/FaceAR \


INCLUDEPATH += \
                /usr/local/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2

INCLUDEPATH += \
                /usr/include/boost \
                /usr/include/tbb \
                /usr/include/eigen3

LIBS += \
        /home/clark/Documents/backup_code/[Completed]/CLM_Server_Upload/FaceAR_PoseEstimateClark_EosCPP_StaticLib_Server/libs/libFaceAR_PoseEstimateClark_EosCPP_StaticLib_Server.a


LIBS += \
        -ltbb \
        -lboost_filesystem -lboost_system -lboost_thread -lboost_program_options


LIBS += \
        -L/usr/local/lib \
        -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_calib3d -lopencv_xfeatures2d -lopencv_imgproc \
        -lopencv_imgcodecs -lopencv_objdetect -lopencv_features2d -lopencv_stitching  -lopencv_video -lopencv_videoio -lopencv_viz \


LIBS += \
        /usr/local/lib/libopencv_calib3d.so \
        /usr/local/lib/libopencv_objdetect.so \
        /usr/local/lib/libopencv_core.so \
        /usr/local/lib/libopencv_videoio.so \
        /usr/local/lib/libopencv_features2d.so \
        /usr/local/lib/libopencv_viz.so \
        /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_xfeatures2d.so \
        /usr/local/lib/libopencv_imgcodecs.so \
        /usr/local/lib/libopencv_imgproc.so

