QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ArchiveTab/archivetab.cpp \
    Batch/batch.cpp \
    ClickableLabel/clickablelabel.cpp \
    DraggableLabel/draggablelabel.cpp \
    GameTab/gametab.cpp \
    MainWindow/mainwindow.cpp \
    Piece/piece.cpp \
    PlayersTab/playerstab.cpp \
    ProfileTab/profiletab.cpp \
    PromotionField/promotionfield.cpp \
    main.cpp

HEADERS += \
    ArchiveTab/archivetab.h \
    Batch/batch.h \
    ClickableLabel/clickablelabel.h \
    DraggableLabel/draggablelabel.h \
    GameTab/gametab.h \
    MainWindow/mainwindow.h \
    Piece/piece.h \
    PlayersTab/playerstab.h \
    ProfileTab/profiletab.h \
    PromotionField/promotionfield.h

FORMS += \
    MainWindow/mainwindow.ui \
    PromotionField/promotionField.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .astylerc \
    model.qmodel
