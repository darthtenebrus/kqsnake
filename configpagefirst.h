//
// Created by esorochinskiy on 14.11.23.
//

#ifndef KQSNAKE_CONFIGPAGEFIRST_H
#define KQSNAKE_CONFIGPAGEFIRST_H

#include <QWidget>
#include "ui_configpagefirst.h"


QT_BEGIN_NAMESPACE
namespace Ui { class ConfigPageFirst; }
QT_END_NAMESPACE

class ConfigPageFirst : public QWidget, public  Ui::ConfigPageFirst {
Q_OBJECT

public:
    explicit ConfigPageFirst(QWidget *parent = nullptr);

protected:
    void changeEvent(QEvent *event) override;

};


#endif //KQSNAKE_CONFIGPAGEFIRST_H
