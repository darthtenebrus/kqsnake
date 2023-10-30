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

protected:
    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *event);

private:

    int m_ScrCellsX;
    int m_ScrCellsY;
    int m_remScrX;
    int m_remScrY;
    int m_cellsX;
    int m_cellsY;
    Snake *mSnake;

    void actualDoRePaint();
    void recalcScreenCells();


    QPoint getStandardFieldDefs(int &x, int &y) const;

    QPoint getMainOffset() const;



    void renewGame();
    void initTotalCells();

};


#endif //KQSNAKE_SNAKEGAME_H
