QT += core gui widgets multimedia multimediawidgets

CONFIG += c++11


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        editscene.cpp \
        app.cpp \
        modularlayout.cpp \
        scene.cpp \
        the_button.cpp \
        the_player.cpp \
        tomeo.cpp \
        video.cpp \
        videomanager.cpp \
        videoplayer.cpp

HEADERS += \
    editscene.h \
    app.h \
    modularlayout.h \
    scene.h \
    the_button.h \
    the_player.h \
    video.h \
    videomanager.h \
    videoplayer.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

