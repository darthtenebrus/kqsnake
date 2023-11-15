//
// Created by esorochinskiy on 30.10.23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "snakegame.h"
#include "version.h"
#include "kqsnake.h"
#include "configpagefirst.h"
#include "configpagesecond.h"
#include <QLayout>
#include <QMessageBox>
#include <QSlider>
#include <KConfigDialog>
#include <KAboutData>
#include <KHelpMenu>


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow),
        timerSlider(new QSlider(Qt::Horizontal, this)) {
    ui->setupUi(this);

    hMenu = new KHelpMenu(this, KAboutData(QStringLiteral("KQsnake"),
                                              tr("Snake Game"), APP_VERSION,
                                              tr("Another Game Of Snake under KDE"),
                                              KAboutLicense::GPL_V3, "© 2023 E.Sorochinskiy",
                                              tr("Control the snake and collect as many apples as you can"),
                                              "https://www.darkguard.net").setTranslator("Eugene E. Sorochinskiy",
                                                                                         "webmaster@darkguard.net"));

    QAction * sw = hMenu->action(KHelpMenu::menuSwitchLanguage);
    hMenu->menu()->removeAction(sw);
    QAction *actionAboutQt;
    hMenu->menu()->insertAction(hMenu->action(KHelpMenu::menuAboutKDE),
                                actionAboutQt = new QAction(tr("About Qt"), this));
    ui->menubar->addMenu(hMenu->menu());

    timerSlider->setValue(5);
    timerSlider->setSliderPosition(5);
    timerSlider->setSingleStep(1);
    timerSlider->setPageStep(1);
    timerSlider->setMinimum(1);
    timerSlider->setMaximum(10);
    timerSlider->setTracking(true);
    timerSlider->setToolTip(tr("Snake Movement Speed"));
    timerSlider->setFixedWidth(200);
    ui->toolBar->addWidget(timerSlider);

    gameField = new SnakeGame(timerSlider->value(), this);
    gameField->setMMaxTurnsBetween(Settings::moves());
    gameField->setMMaxLength(Settings::length());
    gameField->setMBackColor(Settings::backcolor());

    gameField->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
    gameField->setStatusTip(tr("Use right and left arrow keys or A/D keys or mouse buttons to control the snake"));

    ui->centralwidget->layout()->addWidget(gameField);
    gameField->setFocusPolicy(Qt::StrongFocus);
    gameField->setFocus();
    connect(timerSlider, &QSlider::valueChanged, gameField, &SnakeGame::timerChanged);

    connect(ui->actionNewGame, &QAction::triggered, gameField, &SnakeGame::newGameTrigger);
    connect(ui->actionStartStopGame, &QAction::triggered, gameField, &SnakeGame::startStopTrigger);
    connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::settingsTriggered);
    connect(ui->actionShowToolbar, &QAction::triggered, this, [=](bool checked) {
        ui->toolBar->setHidden(!checked);
    });

    connect(ui->actionShowStatusBar, &QAction::triggered, this, [=](bool checked) {
        ui->statusbar->setHidden(!checked);
    });
    connect(actionAboutQt, &QAction::triggered, this, [=](bool checked) {
        QMessageBox::aboutQt(this);
    });
    connect(gameField, &SnakeGame::changeControls, this, &MainWindow::controlsChanged);
    connect(gameField, &SnakeGame::enableStart, this, &MainWindow::startEnable);

}

MainWindow::~MainWindow() {
    delete gameField;
    delete hMenu;
    delete ui;
    delete timerSlider;

}

void MainWindow::controlsChanged(bool active) {
    ui->actionStartStopGame->setIcon(QIcon::fromTheme(
            active ? "media-playback-pause" : "media-playback-start")
            );

}

void MainWindow::startEnable(bool e) {
    ui->actionStartStopGame->setEnabled(e);
}

void MainWindow::settingsTriggered(bool e) {

    auto *dialog = KConfigDialog::exists(QStringLiteral("Settings"));
    if (!dialog) {
        dialog = new KConfigDialog(this, QStringLiteral("Settings"), Settings::self());
        dialog->setFaceType(KPageDialog::List);

        dialog->addPage(new ConfigPageFirst(this), tr("General"), "preferences-system", tr("General"));
        dialog->addPage(new ConfigPageSecond(this), tr("Colors"), "colors-luma", tr("Colors"));
        dialog->setModal(true);
        connect(dialog, &KConfigDialog::settingsChanged, this, &MainWindow::loadSettings);
    }
    dialog->show();
}

void MainWindow::loadSettings(const QString &dName) {

    gameField->setMMaxTurnsBetween(Settings::moves());
    gameField->setMMaxLength(Settings::length());
    gameField->setMBackColor(Settings::backcolor());
    gameField->repaint();
}

