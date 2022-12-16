QT += core gui widgets multimedia multimediawidgets

CONFIG += c++11


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        createprojectscene.cpp \
        editscene.cpp \
        app.cpp \
        modularlayout.cpp \
        primarywindow.cpp \
        project.cpp \
        projectmanager.cpp \
        projectsscene.cpp \
        scene.cpp \
        scenemanager.cpp \
        translationmanager.cpp \
        trimscene.cpp \
        video.cpp \
        videogalleryscene.cpp \
        videomanager.cpp \
        videoplayer.cpp

HEADERS += \
    createprojectscene.h \
    editscene.h \
    app.h \
    modularlayout.h \
    primarywindow.h \
    project.h \
    projectmanager.h \
    projectsscene.h \
    scene.h \
    scenemanager.h \
    translationmanager.h \
    trimscene.h \
    video.h \
    videogalleryscene.h \
    videomanager.h \
    videoplayer.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

TRANSLATIONS = languages/translation_fr.ts languages/translation_meow.ts languages/translation_en.ts

RESOURCES += \
    icons.qrc \
    languages.qrc

