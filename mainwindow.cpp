//
// Created by esorochinskiy on 30.10.23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "snakegame.h"
#include "version.h"
#include "configdialog.h"
#include <QLayout>
#include <QMessageBox>
#include <QSlider>


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow),
        timerSlider(new QSlider(Qt::Horizontal, this)) {
    ui->setupUi(this);

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
    configDialog = new ConfigDialog(this);

    gameField = new SnakeGame(timerSlider->value(), this);
    gameField->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
    gameField->setStatusTip(tr("Use right and left arrow keys or A/D keys or mouse buttons to control the snake"));

    ui->centralwidget->layout()->addWidget(gameField);
    gameField->setFocusPolicy(Qt::StrongFocus);
    gameField->setFocus();
    connect(timerSlider, &QSlider::valueChanged, gameField, &SnakeGame::timerChanged);

    connect(ui->actionNewGame, &QAction::triggered, gameField, &SnakeGame::newGameTrigger);
    connect(ui->actionStartStopGame, &QAction::triggered, gameField, &SnakeGame::startStopTrigger);
    connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::settingsTriggered);
    connect(ui->actionAboutQt, &QAction::triggered, this, [=]{
        QMessageBox::aboutQt(this);

    });

    connect(ui->actionAbout, &QAction::triggered, this, [=]{
        QMessageBox::about(this, "KQsnake",
                           QString("KQsnake v. %1\n").arg(APP_VERSION) +
                           tr("A simple Game Of Snake") +
                           "\n© 2023 E.Sorochinskiy");

    });

    connect(gameField, &SnakeGame::changeControls, this, &MainWindow::controlsChanged);
    connect(gameField, &SnakeGame::enableStart, this, &MainWindow::startEnable);

}

MainWindow::~MainWindow() {
    delete gameField;
    delete configDialog;
    delete ui;
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
    configDialog->setMaxLength(gameField->getMMaxLength());
    configDialog->setBetweenMoves(gameField->getMMaxTurnsBetween());
    configDialog->setModal(true);
    int res = configDialog->exec();
    if (res == QDialog::Accepted) {
        gameField->setMMaxTurnsBetween(configDialog->getBetweenMoves());
        gameField->setMMaxLength(configDialog->getMaxLength());
    }
}
