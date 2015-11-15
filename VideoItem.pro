TEMPLATE = app
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += qml quick core
QT += multimedia

SOURCES += main.cpp \
    videoplayer.cpp \
    videoitem.cpp

HEADERS += \
    videoplayer.h \
    videoitem.h

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)


INCLUDEPATH +=  SDL/include

LIBS += SDL/lib/libSDL.dll.a


INCLUDEPATH +=  ffmpeg/include
LIBS += ffmpeg/lib/libavcodec.dll.a \
        ffmpeg/lib/libavdevice.dll.a \
        ffmpeg/lib/libavfilter.dll.a \
        ffmpeg/lib/libavformat.dll.a \
        ffmpeg/lib/libavutil.dll.a \
        ffmpeg/lib/libpostproc.dll.a \
        ffmpeg/lib/libswscale.dll.a


