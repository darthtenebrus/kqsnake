//
// Created by esorochinskiy on 14.11.23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_configpagefirst.h" resolved

#include "configpagefirst.h"



ConfigPageFirst::ConfigPageFirst(QWidget *parent) :
        QWidget(parent), Ui::ConfigPageFirst() {
    setupUi(this);
    connect(kcfg_showmaluses, &QCheckBox::stateChanged, this, [=](int ch) {
        kcfg_maluses->setEnabled(ch);
    });
}

