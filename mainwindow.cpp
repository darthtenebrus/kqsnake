//
// Created by esorochinskiy on 30.10.23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "snakegame.h"

#include "kqsnake.h"
#include "configpagefirst.h"
#include "configpagesecond.h"

#include <QDesktopWidget>
#include <QSlider>
#include <KConfigDialog>
#include <KToolBar>

#include <KHelpMenu>
#include <KStandardAction>
#include <KActionCollection>
#include <QDomElement>
#ifdef _DEBUG
#include <QDebug>
#endif


MainWindow::MainWindow(QWidget *parent) :
        KXmlGuiWindow(parent) {

    gameField = new SnakeGame(this);

    gameField->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));

    setCentralWidget(gameField);
    gameField->setFocusPolicy(Qt::StrongFocus);
    gameField->setFocus();
    retranslateUi();


    connect(gameField, &SnakeGame::changeControls, this, &MainWindow::controlsChanged);
    connect(gameField, &SnakeGame::enableStart, this, &MainWindow::startEnable);
    setupToolBar();

}

void MainWindow::setupToolBar() {
    QAction *prefAction = KStandardAction::preferences(this, &MainWindow::settingsTriggered, actionCollection());

    prefAction->setWhatsThis(i18n("Open settings dialog"));
    QAction *newGame = actionCollection()->addAction(QStringLiteral("game_new"));
    actionCollection()->setDefaultShortcut(newGame,  Qt::ALT + Qt::Key_N);
    newGame->setText(i18n("New Game"));
    newGame->setIcon(QIcon::fromTheme("document-new"));
    newGame->setWhatsThis(i18n("Clear the field and begin a new game"));
    connect(newGame, &QAction::triggered, gameField, &SnakeGame::newGameTrigger);

    QAction *startStopGame = actionCollection()->addAction(QStringLiteral("game_start_stop"));
    actionCollection()->setDefaultShortcut(startStopGame,  Qt::ALT + Qt::Key_S);
    startStopGame->setText(i18n("Start/Stop Game"));
    startStopGame->setWhatsThis(i18n("Start or stop current game"));
    startStopGame->setIcon(QIcon::fromTheme("media-playback-start"));
    connect(startStopGame, &QAction::triggered, gameField, &SnakeGame::startStopTrigger);

    const QSize &wsize = QApplication::desktop()->size() * 0.9;
    setupGUI(wsize);
    setMinimumSize(wsize);
}

MainWindow::~MainWindow() {
    delete gameField;
}

void MainWindow::controlsChanged(bool active) {
    actionCollection()->action(QStringLiteral("game_start_stop"))->setIcon(QIcon::fromTheme(
            active ? "media-playback-pause" : "media-playback-start")
            );

}

void MainWindow::startEnable(const QString& s) {
    stateChanged(s);
}

void MainWindow::settingsTriggered() {

    auto *dialog = KConfigDialog::exists(QStringLiteral("Settings"));
    if (!dialog) {
        dialog = new KConfigDialog(this, QStringLiteral("Settings"), Settings::self());
        dialog->setFaceType(KPageDialog::List);
        dialog->addPage(new ConfigPageFirst(this), i18n("General"), "preferences-system", i18n("General"));
        dialog->addPage(new ConfigPageSecond(this), i18n("Colors"), "colors-luma", i18n("Colors"));
        dialog->setModal(true);
        connect(dialog, &KConfigDialog::settingsChanged, this, &MainWindow::loadSettings);
    }
    dialog->show();
}

void MainWindow::loadSettings(const QString &) {

    gameField->repaint();
}

void MainWindow::retranslateUi() {
    gameField->setStatusTip(i18n("Use right and left arrow keys or A/D keys or mouse buttons to control the snake"));
    gameField->setWhatsThis(i18n("Use right and left arrow keys or A/D keys or mouse buttons to control the snake"));

}

void MainWindow::changeEvent(QEvent *event) {

    if (event->type() == QEvent::LanguageChange) {
        // This will setup the menu, toolbars etc again, using the new language
        setupGUI(ToolBar | Keys | StatusBar | Create);
        retranslateUi();
    }
    KXmlGuiWindow::changeEvent(event);
}

QStringList MainWindow::customTags() const {

    return KXMLGUIBuilder::customTags() << mSliderTagName;
}

QAction *MainWindow::createCustomElement(QWidget *parent, int index, const QDomElement &element) {

    const QString &tagName = element.tagName().toLower();

    if (tagName == mSliderTagName) {
        QAction *before = nullptr;
        if (index > 0 && index < parent->actions().count()) {
            before = parent->actions().at(index);
        }

        if (auto *bar = qobject_cast<QToolBar *>(parent)) {
            auto *timerSlider = new MySlider(Qt::Horizontal, this);

            timerSlider->retranslateUi();
            connect(timerSlider, &QSlider::valueChanged, gameField, &SnakeGame::timerChanged);
            gameField->setTimerInterval(timerSlider->value());
            auto *res = bar->insertWidget(before, timerSlider);
            return res;
        }

        auto *blank = new QAction(parent);
        blank->setVisible(false);
        parent->insertAction(before, blank);
        return blank;
    } else {
        return KXMLGUIBuilder::createCustomElement(parent, index, element);
    }
}


