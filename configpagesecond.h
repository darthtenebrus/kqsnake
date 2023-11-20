//
// Created by esorochinskiy on 14.11.23.
//

#ifndef KQSNAKE_CONFIGPAGESECOND_H
#define KQSNAKE_CONFIGPAGESECOND_H

#include <QWidget>
#include "ui_configpagesecond.h"


QT_BEGIN_NAMESPACE
namespace Ui { class ConfigPageSecond; }
QT_END_NAMESPACE

class ConfigPageSecond : public QWidget, public Ui::ConfigPageSecond {
Q_OBJECT

public:
    explicit ConfigPageSecond(QWidget *parent = nullptr);

};


#endif //KQSNAKE_CONFIGPAGESECOND_H
