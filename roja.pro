# Add more folders to ship with the application, here
QMLfiles.source = qml/roja
QMLfiles.target = qml

DEPLOYMENTFOLDERS += QMLfiles

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

SOURCES += main.cpp \
    src/model/rojamodel.cpp \
    src/rojadatabase.cpp \
    src/mainwindow.cpp \
    src/lines.cpp \
    src/model/linesmodel.cpp \
    src/model/linesitem.cpp \
    src/model/stopsitem.cpp \
    src/model/stopsmodel.cpp \
    src/stops.cpp \
    src/favs.cpp \
    src/page.cpp \
    src/model/linesstopsitem.cpp \
    src/model/linesstopsmodel.cpp \
    src/model/linesdetailsitem.cpp \
    src/model/linesdetailsmodel.cpp \
    src/timetable.cpp \
    src/routes.cpp \
    src/routeoptions.cpp \
    src/model/routesitem.cpp \
    src/model/routesmodel.cpp \
    src/common.cpp

RESOURCES += common.qrc

HEADERS += \
    src/model/rojamodel.h \
    src/rojadatabase.h \
    src/mainwindow.h \
    src/lines.h \
    src/model/linesmodel.h \
    src/model/linesitem.h \
    src/model/stopsitem.h \
    src/model/stopsmodel.h \
    src/stops.h \
    src/favs.h \
    src/page.h \
    src/model/linesstopsitem.h \
    src/model/linesstopsmodel.h \
    src/model/linesdetailsitem.h \
    src/model/linesdetailsmodel.h \
    src/timetable.h \
    src/routes.h \
    src/routeoptions.h \
    src/model/routesitem.h \
    src/model/routesmodel.h \
    src/common.h

QT += sql network

android {
OTHER_FILES += \
    android/AndroidManifest.xml \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/src/org/kde/necessitas/origo/QtActivity.java \
    android/src/org/kde/necessitas/origo/QtApplication.java \
    android/res/values-fr/strings.xml \
    android/res/values-nl/strings.xml \
    android/res/values-id/strings.xml \
    android/res/values-de/strings.xml \
    android/res/values-ro/strings.xml \
    android/res/values-it/strings.xml \
    android/res/drawable-ldpi/icon.png \
    android/res/values-rs/strings.xml \
    android/res/values-ms/strings.xml \
    android/res/drawable/icon.png \
    android/res/drawable/logo.png \
    android/res/values-el/strings.xml \
    android/res/values-ja/strings.xml \
    android/res/values-zh-rCN/strings.xml \
    android/res/values-zh-rTW/strings.xml \
    android/res/drawable-mdpi/icon.png \
    android/res/values-es/strings.xml \
    android/res/values-pl/strings.xml \
    android/res/drawable-hdpi/icon.png \
    android/res/values-ru/strings.xml \
    android/res/values/strings.xml \
    android/res/values/libs.xml \
    android/res/values-nb/strings.xml \
    android/res/values-et/strings.xml \
    android/res/values-pt-rBR/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/layout/splash.xml
}

symbian {
TARGET.UID3 = 0xE14EA925

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
TARGET.CAPABILITY += NetworkServices
}

# Additional import path used to resolve QML modules in Creator's code model
#QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon

# Add dependency to Symbian components
# CONFIG += qt-components

maemo5 || contains(MEEGO_EDITION,harmattan) {
CONFIG += qdeclarative-boostable
OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    qtc_packaging/debian_fremantle/rules \
    qtc_packaging/debian_fremantle/README \
    qtc_packaging/debian_fremantle/copyright \
    qtc_packaging/debian_fremantle/control \
    qtc_packaging/debian_fremantle/compat \
    qtc_packaging/debian_fremantle/changelog
}

OTHER_FILES += \
    android/version.xml




















































