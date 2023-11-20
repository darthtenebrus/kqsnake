//
// Created by esorochinskiy on 30.10.23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "snakegame.h"

#include "kqsnake.h"
#include "configpagefirst.h"
#include "configpagesecond.h"

#include <QSlider>
#include <KConfigDialog>
#include <KToolBar>

#include <KHelpMenu>
#include <KStandardAction>
#include <KActionCollection>


MainWindow::MainWindow(QWidget *parent) :
        KXmlGuiWindow(parent),
        timerSlider(new QSlider(Qt::Horizontal, this)) {

    timerSlider->setValue(5);
    timerSlider->setSliderPosition(5);
    timerSlider->setSingleStep(1);
    timerSlider->setPageStep(1);
    timerSlider->setMinimum(1);
    timerSlider->setMaximum(10);
    timerSlider->setTracking(true);
    timerSlider->setToolTip(tr("Snake Movement Speed"));
    timerSlider->setWhatsThis(tr("Change Snake Movement Speed dynamically"));
    timerSlider->setFixedWidth(200);

    gameField = new SnakeGame(timerSlider->value(), this);

    gameField->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
    gameField->setStatusTip(tr("Use right and left arrow keys or A/D keys or mouse buttons to control the snake"));
    gameField->setWhatsThis(tr("Use right and left arrow keys or A/D keys or mouse buttons to control the snake"));

    setCentralWidget(gameField);
    gameField->setFocusPolicy(Qt::StrongFocus);
    gameField->setFocus();
    connect(timerSlider, &QSlider::valueChanged, gameField, &SnakeGame::timerChanged);

    connect(gameField, &SnakeGame::changeControls, this, &MainWindow::controlsChanged);
    connect(gameField, &SnakeGame::enableStart, this, &MainWindow::startEnable);
    setupToolBar();

}

void MainWindow::setupToolBar() {
    QAction *prefAction = KStandardAction::preferences(this, &MainWindow::settingsTriggered, actionCollection());
    prefAction->setWhatsThis(tr("Open settings dialog"));
    QAction *newGame = actionCollection()->addAction(QStringLiteral("game_new"));
    actionCollection()->setDefaultShortcut(newGame,  Qt::ALT + Qt::Key_N);
    newGame->setText(tr("New Game"));
    newGame->setIcon(QIcon::fromTheme("document-new"));
    newGame->setWhatsThis(tr("Clear the field and begin a new game"));
    connect(newGame, &QAction::triggered, gameField, &SnakeGame::newGameTrigger);

    QAction *startStopGame = actionCollection()->addAction(QStringLiteral("game_start_stop"));
    actionCollection()->setDefaultShortcut(startStopGame,  Qt::ALT + Qt::Key_S);
    startStopGame->setText(tr("Start/Stop Game"));
    startStopGame->setWhatsThis(tr("Start or stop current game"));
    startStopGame->setIcon(QIcon::fromTheme("media-playback-start"));
    connect(startStopGame, &QAction::triggered, gameField, &SnakeGame::startStopTrigger);

    setupGUI();
    toolBar()->addAction(prefAction);
    toolBar()->addSeparator();
    toolBar()->addWidget(timerSlider);
}

MainWindow::~MainWindow() {
    delete gameField;
}

void MainWindow::controlsChanged(bool active) {
    actionCollection()->action(QStringLiteral("game_start_stop"))->setIcon(QIcon::fromTheme(
            active ? "media-playback-pause" : "media-playback-start")
            );

}

void MainWindow::startEnable(bool e) {
    e ? stateChanged(QStringLiteral("gameplay_state")) :
        stateChanged(QStringLiteral("finished_state"));
}

void MainWindow::settingsTriggered() {

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

    gameField->repaint();
}


