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


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    gameField = new SnakeGame(this);
    gameField->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));

    ui->centralwidget->layout()->addWidget(gameField);
    gameField->setFocusPolicy(Qt::StrongFocus);
    connect(ui->actionNewGame, &QAction::triggered, gameField, &SnakeGame::newGameTrigger);
    connect(ui->actionAboutQt, &QAction::triggered, this, [=]{
        QMessageBox::aboutQt(this);

    });

    connect(ui->actionAbout, &QAction::triggered, this, [=]{
        QMessageBox::about(this, "KQsnake",
                           QString("KQsnake v. %1\n").arg(APP_VERSION) +
                           tr("A simple Game Of Snake") +
                           "\n© 2023 E.Sorochinskiy");

    });



}

MainWindow::~MainWindow() {
    delete gameField;
    delete ui;
}
