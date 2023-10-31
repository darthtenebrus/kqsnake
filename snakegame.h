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
    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *event);

private:

    int m_ScrCellsX;
    int m_ScrCellsY;
    int m_remScrX;
    int m_remScrY;
    int m_cellsX;
    int m_cellsY;
    Snake *mSnake = nullptr;
    QList<GameObject> *mApples = nullptr;
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
};


#endif //KQSNAKE_SNAKEGAME_H
