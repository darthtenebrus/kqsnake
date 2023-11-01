//
// Created by esorochinskiy on 30.10.23.
//

#ifndef KQSNAKE_SNAKEGAME_H
#define KQSNAKE_SNAKEGAME_H


#include <QWidget>
#include "snake.h"

class SnakeGame : public QWidget {
Q_OBJECT
public:
    SnakeGame(QWidget *parent = nullptr);
    ~SnakeGame() override;

    int getScreenCellsX();
    int getScreenCellsY();

    int getMemCellsX();
    int getMemCellsY();

    QList<GameObject> *getApples();

protected:
    void paintEvent(QPaintEvent *e) override;
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:

    int m_ScrCellsX;
    int m_ScrCellsY;
    int m_remScrX;
    int m_remScrY;
    int m_cellsX;
    int m_cellsY;
    int maxTurnsBefore = 0;
    int m_TimerInterval;
    Snake *mSnake = nullptr;
    QList<GameObject> *mApples = nullptr;
    QTimer *mTimer = nullptr;

    QBrush mEmpty;
    QBrush mBody;
    QBrush mAppleColor;

    void actualDoRePaint();
    void recalcScreenCells();
    void createNewApple(bool);


    QPoint getStandardFieldDefs(int &x, int &y) const;

    [[nodiscard]] QPoint getMainOffset() const;



    void renewGame(bool);
    void initTotalCells();
    void drawApples( QPainter &);

    int localRand(int);
    bool collizedApple(int x, int y);
    void cancelTimerInstantly();
    void startGame();

public slots:
    void newGameTrigger(bool);
private slots:
    void nextMove(void);
};


#endif //KQSNAKE_SNAKEGAME_H
