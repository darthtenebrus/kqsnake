//
// Created by esorochinskiy on 30.10.23.
//

#include <QPainter>
#include <QApplication>
#include "snakegame.h"
#define FIELD_OFFSET 1
#define SPACE 1
#define MIN_CELL_SIZE 16
#ifdef _DEBUG
#include <QDebug>
#include <QDesktopWidget>

#endif


SnakeGame::SnakeGame(QWidget *parent) : QWidget(parent) {
    initTotalCells();
    renewGame();
}

SnakeGame::~SnakeGame() {
    delete mSnake;
}

void SnakeGame::resizeEvent(QResizeEvent *event) {
    recalcScreenCells();
    QWidget::resizeEvent(event);

}

void SnakeGame::recalcScreenCells() {
    int h = height();
    int w = width();
    QPoint fd = getStandardFieldDefs(w, h);

    m_ScrCellsX = fd.x() / (MIN_CELL_SIZE + SPACE);
    m_ScrCellsY = fd.y() / (MIN_CELL_SIZE + SPACE);
    m_remScrX = (fd.x() - (MIN_CELL_SIZE + SPACE) * m_ScrCellsX) / 2;
    m_remScrY = (fd.y() - (MIN_CELL_SIZE + SPACE) * m_ScrCellsY) / 2;



}

QPoint SnakeGame::getStandardFieldDefs(int &x, int &y) const {
    return {x - (FIELD_OFFSET + SPACE) * 2, y - (FIELD_OFFSET + SPACE) * 2};
}


void SnakeGame::paintEvent(QPaintEvent *e) {
    actualDoRePaint();
}

QPoint SnakeGame::getMainOffset() const {
    return {FIELD_OFFSET + SPACE + m_remScrX, FIELD_OFFSET + SPACE + m_remScrY};
}


void SnakeGame::actualDoRePaint() {

    QPainter painter(this);

    painter.setBackground(QBrush("#232323"));

    const QPoint &mainOffset = getMainOffset();
    painter.translate(mainOffset.x(), mainOffset.y());
    for (int y = 0; y < m_ScrCellsY; ++y) {
        for (int x = 0; x < m_ScrCellsX; ++x) {
            QBrush color;

            color = QBrush("#000000");
            for (GameObject &obj : *mSnake->getParts()) {
                if (obj.intersects(x, y)) {
                    color = QBrush("#00FF00");
                    break;
                }
            }
            painter.fillRect(QRect(x * (MIN_CELL_SIZE + SPACE), y * (MIN_CELL_SIZE + SPACE),
                                   MIN_CELL_SIZE, MIN_CELL_SIZE), color);

        }

    }
}

void SnakeGame::renewGame() {

    if (!mSnake) {
        delete mSnake;
    }

    mSnake = new Snake(m_cellsX / 2, m_cellsY / 2);

}


void SnakeGame::initTotalCells() {

    QDesktopWidget *desktopwidget = QApplication::desktop(); // Get display resolution
    int dw = desktopwidget->width();
    int dh = desktopwidget->height();
    QPoint fd = getStandardFieldDefs(dw, dh);

    m_cellsX = fd.x() / (MIN_CELL_SIZE + SPACE);
    m_cellsY = fd.y() / (MIN_CELL_SIZE + SPACE);

}


