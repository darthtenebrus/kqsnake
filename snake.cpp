//
// Created by esorochinskiy on 30.10.23.
//

#include <QPainter>
#include "snake.h"
#include "constants.h"

Snake::Snake(int x, int y, QBrush &color) {
    mSnakeParts = new QQueue<GameObject>();
    for (int i = 2; i >= 0; i--) {
        mSnakeParts->enqueue(GameObject(x + i, y, color));
    }
}

Snake::~Snake() {
    delete mSnakeParts;
}

void Snake::drawInitial(QPainter &painter) {
    for(GameObject &obj : *mSnakeParts) {
        painter.fillRect(QRect(obj.x() * (MIN_CELL_SIZE + SPACE), obj.y() * (MIN_CELL_SIZE + SPACE),
                               MIN_CELL_SIZE, MIN_CELL_SIZE), obj.getColor());
    }
}


