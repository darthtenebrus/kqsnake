//
// Created by esorochinskiy on 14.11.23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ConfigPageSecond.h" resolved

#include "configpagesecond.h"


ConfigPageSecond::ConfigPageSecond(QWidget *parent) :
        QWidget(parent), Ui::ConfigPageSecond() {
    setupUi(this);
}

void ConfigPageSecond::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // This will setup the menu, toolbars etc again, using the new language
        retranslateUi(this);
    }
    QWidget::changeEvent(event);
}


