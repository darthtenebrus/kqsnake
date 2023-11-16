//
// Created by esorochinskiy on 14.11.23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_configpagefirst.h" resolved

#include "configpagefirst.h"
#include "ui_configpagefirst.h"


ConfigPageFirst::ConfigPageFirst(QWidget *parent) :
        QWidget(parent), ui(new Ui::ConfigPageFirst) {
    ui->setupUi(this);
    connect(ui->kcfg_showmaluses, &QCheckBox::stateChanged, this, [=](int ch) {
        ui->kcfg_maluses->setEnabled(ch);
    });
}

ConfigPageFirst::~ConfigPageFirst() {
    delete ui;
}
