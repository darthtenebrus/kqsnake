//
// Created by esorochinskiy on 08.11.23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ConfigDialog.h" resolved

#include "configdialog.h"
#include "ui_configdialog.h"
#include <QPushButton>

ConfigDialog::ConfigDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::ConfigDialog) {
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked,
            this, &QDialog::accept);
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked,
            this, &QDialog::reject);

}

ConfigDialog::~ConfigDialog() {
    delete ui;
}

int ConfigDialog::getMaxLength() const {
    return ui->snakeLength->value();
}

int ConfigDialog::getBetweenMoves() const {
    return ui->movesBetween->value();
}

void ConfigDialog::setMaxLength(int len) {
    ui->snakeLength->setValue(len);
}

void ConfigDialog::setBetweenMoves(int between) {
    ui->movesBetween->setValue(between);
}

