QT       += core gui
QT += bluetooth
QT += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ArchiveTab/archivetab.cpp \
    Batch/batch.cpp \
    BatchList/batchlist.cpp \
    BluetoothClient/bluetoothclient.cpp \
    BluetoothServer/bluetoothserver.cpp \
    ClickableLabel/clickablelabel.cpp \
    DraggableLabel/draggablelabel.cpp \
    GameTab/gametab.cpp \
    MainWindow/mainwindow.cpp \
    Piece/piece.cpp \
    PromotionField/promotionfield.cpp \
    ThreadClient/threadclient.cpp \
    ThreadServer/threadserver.cpp \
    main.cpp

HEADERS += \
    ArchiveTab/archivetab.h \
    Batch/batch.h \
    BatchList/batchlist.h \
    BluetoothClient/bluetoothclient.h \
    BluetoothServer/bluetoothserver.h \
    ClickableLabel/clickablelabel.h \
    DraggableLabel/draggablelabel.h \
    GameTab/gametab.h \
    MainWindow/mainwindow.h \
    Piece/piece.h \
    PromotionField/promotionfield.h \
    ThreadClient/threadclient.h \
    ThreadServer/threadserver.h

FORMS += \
    BatchList/batchlist.ui \
    MainWindow/mainwindow.ui \
    PromotionField/promotionField.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .astylerc \
    model.qmodel

INCLUDEPATH += C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\um\x64\WS2_32.lib

# Добавляем библиотеку для компоновки с проектом
LIBS += -lws2_32

RESOURCES += \
    resources.qrc
