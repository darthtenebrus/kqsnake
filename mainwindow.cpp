//
// Created by esorochinskiy on 30.10.23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "snakegame.h"
#include "version.h"
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

    gameField = new SnakeGame(timerSlider->value(), this);
    gameField->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));

    ui->centralwidget->layout()->addWidget(gameField);
    gameField->setFocusPolicy(Qt::StrongFocus);
    gameField->setFocus();
    connect(timerSlider, &QSlider::valueChanged, gameField, &SnakeGame::timerChanged);

    connect(ui->actionNewGame, &QAction::triggered, gameField, &SnakeGame::newGameTrigger);
    connect(ui->actionStartStopGame, &QAction::triggered, gameField, &SnakeGame::startStopTrigger);
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
