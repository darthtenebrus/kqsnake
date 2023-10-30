//
// Created by esorochinskiy on 30.10.23.
//

#include <QColor>
#include "snake.h"
#include <QBrush>

Snake::Snake(int x, int y, QBrush &empty, QBrush &body) : mEmpty(empty), mBody(body) {
    mSnakeParts = new QQueue<GameObject>();
    for (int i = 2; i >= 0; i--) {
        mSnakeParts->enqueue(GameObject(x + i, y));
    }
}

Snake::~Snake() {
    delete mSnakeParts;
}

QBrush &Snake::colorize(int x, int y) {
    for (GameObject &obj : *mSnakeParts) {
        if (obj.intersects(x, y)) {
            return mBody;
        }
    }
    return mEmpty;
}
