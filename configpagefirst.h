//
// Created by esorochinskiy on 14.11.23.
//

#ifndef KQSNAKE_CONFIGPAGEFIRST_H
#define KQSNAKE_CONFIGPAGEFIRST_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class ConfigPageFirst; }
QT_END_NAMESPACE

class ConfigPageFirst : public QWidget {
Q_OBJECT

public:
    explicit ConfigPageFirst(QWidget *parent = nullptr);

    ~ConfigPageFirst() override;

private:
    Ui::ConfigPageFirst *ui;
};


#endif //KQSNAKE_CONFIGPAGEFIRST_H
