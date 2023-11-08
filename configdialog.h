//
// Created by esorochinskiy on 08.11.23.
//

#ifndef KQSNAKE_CONFIGDIALOG_H
#define KQSNAKE_CONFIGDIALOG_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class ConfigDialog; }
QT_END_NAMESPACE

class ConfigDialog : public QDialog {
Q_OBJECT

public:
    explicit ConfigDialog(QWidget *parent = nullptr);

    ~ConfigDialog() override;

    [[nodiscard]]
    int getMaxLength() const;

    [[nodiscard]]
    int getBetweenMoves() const;

    void setMaxLength(int);
    void setBetweenMoves(int);

private:
    Ui::ConfigDialog *ui;
};


#endif //KQSNAKE_CONFIGDIALOG_H
