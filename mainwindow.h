//
// Created by esorochinskiy on 30.10.23.
//

#ifndef KQSNAKE_MAINWINDOW_H
#define KQSNAKE_MAINWINDOW_H

#include <QSlider>
#include <KAboutData>
#include <KHelpMenu>
#include <KMainWindow>

#include "snakegame.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public KMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    SnakeGame *gameField;
    QSlider *timerSlider;
    KHelpMenu *hMenu;


private slots:
    void loadSettings(const QString &);

public slots:
    void controlsChanged(bool);
    void startEnable(bool);
    void settingsTriggered(bool);

};


#endif //KQSNAKE_MAINWINDOW_H
