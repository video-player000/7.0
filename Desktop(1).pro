QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QT += sql

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


INCLUDEPATH += $$PWD/ffmpeg-5.0.1-full_build-shared/include \
               $$PWD/SDL2-2.0.22/include
              # $$PWD/soundtouch/include \

LIBS += $$PWD/ffmpeg-5.0.1-full_build-shared/lib/avcodec.lib \
        $$PWD/ffmpeg-5.0.1-full_build-shared/lib/avdevice.lib \
        $$PWD/ffmpeg-5.0.1-full_build-shared/lib/avfilter.lib \
        $$PWD/ffmpeg-5.0.1-full_build-shared/lib/avformat.lib \
        $$PWD/ffmpeg-5.0.1-full_build-shared/lib/avutil.lib \
        $$PWD/ffmpeg-5.0.1-full_build-shared/lib/postproc.lib \
        $$PWD/ffmpeg-5.0.1-full_build-shared/lib/swresample.lib \
        $$PWD/ffmpeg-5.0.1-full_build-shared/lib/swscale.lib \
        $$PWD/SDL2-2.0.22/lib/x64/SDL2.lib \
        $$PWD/SDL2-2.0.22/lib/x64/SDL2main.lib \
        $$PWD/SDL2-2.0.22/lib/x64/SDL2test.lib \
#        $$PWD/soundtouch/lib/SoundTouchD_x64.lib


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    core.cpp \
    console.cpp \
    display.cpp \
    seekwidget.cpp \
    file.cpp \
    medialibrary.cpp

HEADERS += \
    mainwindow.h \
    core.h \
    console.h \
    display.h \
    seekwidget.h \
    file.h \
    medialibrary.h

FORMS += \
    console.ui \
    medialibrary.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    icon/last.png \
    icon/love_0.png \
    icon/love_1.png \
    icon/next.png \
    icon/order_random.png \
    icon/order_sequential.png \
    icon/order_single.png \
    icon/play_off.png \
    icon/play_on.png \
    icon/screen_full.png \
    icon/screen_window.png \
    icon/set.png \
    icon/speed_0.5.png \
    icon/speed_1.0.png \
    icon/speed_2.0.png \
    icon/speed_4.0.png \
    icon/speed_8.0.png \
    icon/upend.png \
    icon/voice_off.png \
    icon/voice_on.png

unix|win32: LIBS += -L$$PWD/soundtouch/lib/ -lSoundTouchD_x64

INCLUDEPATH += $$PWD/soundtouch/include
DEPENDPATH += $$PWD/soundtouch/include

RESOURCES += \
    Resources.qrc
