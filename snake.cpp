//
// Created by esorochinskiy on 30.10.23.
//

#include <QPainter>
#include "snake.h"
#include "constants.h"

Snake::Snake(int x, int y, QBrush &color)  : QQueue<GameObject>() {
    for (int i = 2; i >= 0; i--) {
        enqueue(GameObject(x + i, y, color));
    }
}


void Snake::drawInitial(QPainter &painter) {
    for(GameObject &obj : *this) {
        painter.fillRect(QRect(obj.x() * (MIN_CELL_SIZE + SPACE), obj.y() * (MIN_CELL_SIZE + SPACE),
                               MIN_CELL_SIZE, MIN_CELL_SIZE), obj.getColor());
    }
}


