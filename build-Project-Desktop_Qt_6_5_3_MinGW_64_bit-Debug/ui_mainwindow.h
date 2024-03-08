/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *game;
    QGridLayout *gameGridLayout;
    QLabel *opponentLabel;
    QTabWidget *gameTabWidget;
    QWidget *settings;
    QGridLayout *settingsGridLayout;
    QPushButton *playButton;
    QPushButton *minutes10Button;
    QPushButton *minutes3Button;
    QPushButton *minute1Button;
    QPushButton *minutes30Button;
    QLabel *label;
    QPushButton *minutes15Button;
    QPushButton *minutes5Button;
    QSpacerItem *verticalSpacer;
    QWidget *moves;
    QGridLayout *movesGridLayout;
    QListWidget *moveList;
    QPushButton *offerADrawButton;
    QPushButton *giveUpButton;
    QWidget *widget;
    QWidget *players;
    QWidget *archive;
    QWidget *profile;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(847, 687);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(847, 687));
        MainWindow->setMaximumSize(QSize(847, 687));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        game = new QWidget();
        game->setObjectName("game");
        gameGridLayout = new QGridLayout(game);
        gameGridLayout->setObjectName("gameGridLayout");
        opponentLabel = new QLabel(game);
        opponentLabel->setObjectName("opponentLabel");
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(opponentLabel->sizePolicy().hasHeightForWidth());
        opponentLabel->setSizePolicy(sizePolicy1);

        gameGridLayout->addWidget(opponentLabel, 0, 0, 1, 1);

        gameTabWidget = new QTabWidget(game);
        gameTabWidget->setObjectName("gameTabWidget");
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(gameTabWidget->sizePolicy().hasHeightForWidth());
        gameTabWidget->setSizePolicy(sizePolicy2);
        gameTabWidget->setMaximumSize(QSize(500, 1000));
        settings = new QWidget();
        settings->setObjectName("settings");
        settingsGridLayout = new QGridLayout(settings);
        settingsGridLayout->setObjectName("settingsGridLayout");
        playButton = new QPushButton(settings);
        playButton->setObjectName("playButton");
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(playButton->sizePolicy().hasHeightForWidth());
        playButton->setSizePolicy(sizePolicy3);

        settingsGridLayout->addWidget(playButton, 8, 0, 1, 1);

        minutes10Button = new QPushButton(settings);
        minutes10Button->setObjectName("minutes10Button");
        sizePolicy3.setHeightForWidth(minutes10Button->sizePolicy().hasHeightForWidth());
        minutes10Button->setSizePolicy(sizePolicy3);

        settingsGridLayout->addWidget(minutes10Button, 4, 0, 1, 1);

        minutes3Button = new QPushButton(settings);
        minutes3Button->setObjectName("minutes3Button");
        sizePolicy3.setHeightForWidth(minutes3Button->sizePolicy().hasHeightForWidth());
        minutes3Button->setSizePolicy(sizePolicy3);

        settingsGridLayout->addWidget(minutes3Button, 2, 0, 1, 1);

        minute1Button = new QPushButton(settings);
        minute1Button->setObjectName("minute1Button");
        sizePolicy3.setHeightForWidth(minute1Button->sizePolicy().hasHeightForWidth());
        minute1Button->setSizePolicy(sizePolicy3);

        settingsGridLayout->addWidget(minute1Button, 1, 0, 1, 1);

        minutes30Button = new QPushButton(settings);
        minutes30Button->setObjectName("minutes30Button");
        sizePolicy3.setHeightForWidth(minutes30Button->sizePolicy().hasHeightForWidth());
        minutes30Button->setSizePolicy(sizePolicy3);

        settingsGridLayout->addWidget(minutes30Button, 6, 0, 1, 1);

        label = new QLabel(settings);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignCenter);

        settingsGridLayout->addWidget(label, 0, 0, 1, 1);

        minutes15Button = new QPushButton(settings);
        minutes15Button->setObjectName("minutes15Button");
        sizePolicy3.setHeightForWidth(minutes15Button->sizePolicy().hasHeightForWidth());
        minutes15Button->setSizePolicy(sizePolicy3);

        settingsGridLayout->addWidget(minutes15Button, 5, 0, 1, 1);

        minutes5Button = new QPushButton(settings);
        minutes5Button->setObjectName("minutes5Button");
        sizePolicy3.setHeightForWidth(minutes5Button->sizePolicy().hasHeightForWidth());
        minutes5Button->setSizePolicy(sizePolicy3);

        settingsGridLayout->addWidget(minutes5Button, 3, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        settingsGridLayout->addItem(verticalSpacer, 7, 0, 1, 1);

        gameTabWidget->addTab(settings, QString());
        moves = new QWidget();
        moves->setObjectName("moves");
        movesGridLayout = new QGridLayout(moves);
        movesGridLayout->setObjectName("movesGridLayout");
        moveList = new QListWidget(moves);
        moveList->setObjectName("moveList");

        movesGridLayout->addWidget(moveList, 0, 0, 1, 2);

        offerADrawButton = new QPushButton(moves);
        offerADrawButton->setObjectName("offerADrawButton");

        movesGridLayout->addWidget(offerADrawButton, 1, 0, 1, 1);

        giveUpButton = new QPushButton(moves);
        giveUpButton->setObjectName("giveUpButton");

        movesGridLayout->addWidget(giveUpButton, 1, 1, 1, 1);

        gameTabWidget->addTab(moves, QString());

        gameGridLayout->addWidget(gameTabWidget, 0, 1, 2, 1);

        widget = new QWidget(game);
        widget->setObjectName("widget");
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(512, 512));

        gameGridLayout->addWidget(widget, 1, 0, 1, 1);

        tabWidget->addTab(game, QString());
        players = new QWidget();
        players->setObjectName("players");
        tabWidget->addTab(players, QString());
        archive = new QWidget();
        archive->setObjectName("archive");
        tabWidget->addTab(archive, QString());
        profile = new QWidget();
        profile->setObjectName("profile");
        tabWidget->addTab(profile, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 847, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        gameTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        opponentLabel->setText(QCoreApplication::translate("MainWindow", "Opponent", nullptr));
        playButton->setText(QCoreApplication::translate("MainWindow", "Play", nullptr));
        minutes10Button->setText(QCoreApplication::translate("MainWindow", "10 minutes", nullptr));
        minutes3Button->setText(QCoreApplication::translate("MainWindow", "3 minutes", nullptr));
        minute1Button->setText(QCoreApplication::translate("MainWindow", "1 minute", nullptr));
        minutes30Button->setText(QCoreApplication::translate("MainWindow", "30 minutes", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Choose time control:", nullptr));
        minutes15Button->setText(QCoreApplication::translate("MainWindow", "15 minutes", nullptr));
        minutes5Button->setText(QCoreApplication::translate("MainWindow", "5 minutes", nullptr));
        gameTabWidget->setTabText(gameTabWidget->indexOf(settings), QCoreApplication::translate("MainWindow", "Settings", nullptr));
        offerADrawButton->setText(QCoreApplication::translate("MainWindow", "Offer a draw", nullptr));
        giveUpButton->setText(QCoreApplication::translate("MainWindow", "Give up", nullptr));
        gameTabWidget->setTabText(gameTabWidget->indexOf(moves), QCoreApplication::translate("MainWindow", "Moves", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(game), QCoreApplication::translate("MainWindow", "Game", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(players), QCoreApplication::translate("MainWindow", "Players", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(archive), QCoreApplication::translate("MainWindow", "Archive", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(profile), QCoreApplication::translate("MainWindow", "Profile", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
