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
    mDir = LEFT;
    mColor = color;
}


void Snake::drawInitial(QPainter &painter) {
    for(GameObject &obj : *this) {
        painter.fillRect(QRect(obj.x() * (MIN_CELL_SIZE + SPACE), obj.y() * (MIN_CELL_SIZE + SPACE),
                               MIN_CELL_SIZE, MIN_CELL_SIZE), obj.getColor());
    }
}

void Snake::setDirection(Direction d) {
    if (!isOpposed(mDir, d)) {
        mDir = d;
    }
}

bool Snake::isOpposed(const Direction &current, const Direction &candidate) const {

    switch (current) {
        case UP:
            return candidate == DOWN;
        case DOWN:
            return candidate == UP;
        case LEFT:
            return candidate == RIGHT;
        case RIGHT:
            return candidate == LEFT;
    }
    return false;

}

bool Snake::checkCollision(const GameObject &other) {
    return std::any_of(begin(), end(), [&](const GameObject &g) {
        return g.intersects(other);
    });
}

GameObject Snake::createNewHead()  {
    GameObject oldHead = last();
    int newHeadX = oldHead.x();
    int newHeadY = oldHead.y();
    switch (mDir) {
        case LEFT:
            newHeadX--;
            break;
        case DOWN:
            newHeadY++;
            break;
        case RIGHT:
            newHeadX++;
            break;
        case UP:
            newHeadY--;
            break;
    }

    return { newHeadX, newHeadY, mColor };
}

void Snake::removeTail() {
    dequeue();
}


