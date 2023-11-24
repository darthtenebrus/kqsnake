//
// Created by esorochinskiy on 30.10.23.
//

#ifndef KQSNAKE_MAINWINDOW_H
#define KQSNAKE_MAINWINDOW_H

#include <KAboutData>
#include <KXmlGuiWindow>

#include "snakegame.h"
#include "myslider.h"

class MainWindow : public KXmlGuiWindow {
Q_OBJECT

protected:
    void changeEvent(QEvent *event) override;

public:
    [[nodiscard]]
    QStringList customTags() const override;

    QAction *createCustomElement(QWidget *parent, int index, const QDomElement &element) override;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    SnakeGame *gameField;
    void setupToolBar();
    void retranslateUi();
    QString mSliderTagName = "slider";

private slots:
    void loadSettings(const QString &);

public slots:
    void controlsChanged(bool);
    void startEnable(const QString &);
    void settingsTriggered();

};


#endif //KQSNAKE_MAINWINDOW_H
