QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    atimeloggerrequest.cpp \
    auth.cpp \
    main.cpp \
    mainwindow.cpp \
    recordrequester.cpp \
    ui/choosetimedialog.cpp \
    ui/loginscreendialog.cpp

HEADERS += \
    atimeloggerrequest.h \
    auth.h \
    mainwindow.h \
    recordrequester.h \
    ui/choosetimedialog.h \
    ui/loginscreendialog.h

FORMS += \
    mainwindow.ui \
    ui/choosetimedialog.ui \
    ui/loginscreendialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
