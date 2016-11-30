#-------------------------------------------------
#
# Project created by QtCreator 2016-11-01T16:43:08
#
#-------------------------------------------------

QT       += core gui sensors websockets
android: QT += androidextras
ios: LIBS += -framework AudioToolbox
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = quarre_phone
TEMPLATE = app

SOURCES += main.cpp\
    ws/websocketmanager.cpp \
    os/osbridge.cpp \
    interactions/modules/modulemanager.cpp \
    interactions/modules/interactionmodule.cpp \
    control/control.cpp \
    sensors/sensormanager.cpp \
    views/countdownwidget.cpp \
    views/mainwindow.cpp \
    data/userdatamanager.cpp \
    control/scenariofollower.cpp \
    interactions/models/interaction.cpp \
    interactions/db/interactiondatabase.cpp \
    interactions/modules/touchspatmodule.cpp \
    interactions/modules/zrotationspatmodule.cpp \
    interactions/modules/logininteraction.cpp \
    interactions/modules/textviewer.cpp \
    interactions/modules/introduction.cpp \
    interactions/modules/nullmodule.cpp \
    interactions/modules/subelements/pad.cpp \
    interactions/modules/gesture.cpp \
    views/networkpopupwindow.cpp \
    interactions/modules/loopcontrol.cpp

HEADERS  += ws/websocketmanager.h \
    os/osbridge.h \
    interactions/modules/modulemanager.h \
    interactions/modules/interactionmodule.h \
    control/control.h \
    sensors/sensormanager.h \
    views/countdownwidget.h \
    views/mainwindow.h \
    data/userdatamanager.h \
    control/scenariofollower.h \
    interactions/models/interaction.h \
    interactions/db/interactiondatabase.h \
    interactions/modules/touchspatmodule.h \
    interactions/modules/zrotationspatmodule.h \
    _fwd/fwd_enum.h \
    interactions/modules/logininteraction.h \
    interactions/modules/textviewer.h \
    interactions/modules/introduction.h \
    interactions/modules/nullmodule.h \
    interactions/modules/subelements/pad.h \
    interactions/modules/gesture.h \
    views/networkpopupwindow.h \
    interactions/modules/loopcontrol.h

FORMS    += views/mainwindow.ui

CONFIG += mobility
MOBILITY = 

DISTFILES += \
    interactions/db/interactions.json \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

RESOURCES += \
    interactions/db/resources.qrc

