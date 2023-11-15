//
// Created by esorochinskiy on 14.11.23.
//

#ifndef KQSNAKE_CONFIGPAGESECOND_H
#define KQSNAKE_CONFIGPAGESECOND_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class ConfigPageSecond; }
QT_END_NAMESPACE

class ConfigPageSecond : public QWidget {
Q_OBJECT

public:
    explicit ConfigPageSecond(QWidget *parent = nullptr);

    ~ConfigPageSecond() override;

private:
    Ui::ConfigPageSecond *ui;
};


#endif //KQSNAKE_CONFIGPAGESECOND_H
