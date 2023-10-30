//
// Created by esorochinskiy on 30.10.23.
//

#ifndef KQSNAKE_MAINWINDOW_H
#define KQSNAKE_MAINWINDOW_H

#include <QMainWindow>
#include "snakegame.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    SnakeGame *gameField;
};


#endif //KQSNAKE_MAINWINDOW_H
