//
// Created by esorochinskiy on 30.10.23.
//

#ifndef KQSNAKE_MAINWINDOW_H
#define KQSNAKE_MAINWINDOW_H

#include <QSlider>
#include <KAboutData>
#include <KXmlGuiWindow>

#include "snakegame.h"

class MainWindow : public KXmlGuiWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    SnakeGame *gameField;
    QSlider *timerSlider;
    void setupToolBar();

private slots:
    void loadSettings(const QString &);

public slots:
    void controlsChanged(bool);
    void startEnable(bool);
    void settingsTriggered();

};


#endif //KQSNAKE_MAINWINDOW_H
