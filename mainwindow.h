//
// Created by esorochinskiy on 30.10.23.
//

#ifndef KQSNAKE_MAINWINDOW_H
#define KQSNAKE_MAINWINDOW_H

#include <KAboutData>
#include <KXmlGuiWindow>

#include "snakegame.h"
#include "myslider.h"

class MainWindow : public KXmlGuiWindow {
Q_OBJECT

protected:
    void changeEvent(QEvent *event) override;


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    SnakeGame *gameField;
    MySlider *mySlider;
    void setupToolBar();
    void retranslateUi();

private slots:
    void loadSettings(const QString &);

public slots:
    void controlsChanged(bool);
    void startEnable(const QString &);
    void settingsTriggered();

};


#endif //KQSNAKE_MAINWINDOW_H
