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

SOURCES += main.cpp \
    core/control/control.cpp \
    core/control/scenariofollower.cpp \
    core/interactions/interaction.cpp \
    core/interactions/interactiondatabase.cpp \
    core/interactions/modulemanager.cpp \
    core/network/websocketmanager.cpp \
    core/platform/osbridge.cpp \
    core/sensors/sensormanager.cpp \
    core/views/countdownwidget.cpp \
    core/views/mainwindow.cpp \
    core/views/networkpopupwindow.cpp

HEADERS  += \
    plugins/quarreplugininterface.h \
    core/control/control.h \
    core/control/scenariofollower.h \
    core/interactions/interaction.h \
    core/interactions/interactiondatabase.h \
    core/interactions/modulemanager.h \
    core/network/websocketmanager.h \
    core/platform/osbridge.h \
    core/sensors/sensormanager.h \
    core/views/countdownwidget.h \
    core/views/mainwindow.h \
    core/views/networkpopupwindow.h

CONFIG += mobility
MOBILITY = 

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

# libs/plugins have to be placed in: $$PWD/android/libs/[target-platform] (meaning armeabi-v7a or x86)
# interaction .json namespace files should be put in the $$PWD/android/assets folder
ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

RESOURCES += \
    core/resources/resources.qrc
