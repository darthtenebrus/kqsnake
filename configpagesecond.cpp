//
// Created by esorochinskiy on 14.11.23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ConfigPageSecond.h" resolved

#include "configpagesecond.h"
#include "ui_configpagesecond.h"


ConfigPageSecond::ConfigPageSecond(QWidget *parent) :
        QWidget(parent), ui(new Ui::ConfigPageSecond) {
    ui->setupUi(this);
}

ConfigPageSecond::~ConfigPageSecond() {
    delete ui;
}
