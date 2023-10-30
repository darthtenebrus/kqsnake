//
// Created by esorochinskiy on 30.10.23.
//

#include <QColor>
#include "snake.h"
#include <QBrush>

Snake::Snake(int x, int y) {
    mSnakeParts = new QList<GameObject>();
    for (int i = 0; i < 3; i++) {
        mSnakeParts->append(GameObject(x + i, y));
    }
}

Snake::~Snake() {
    delete mSnakeParts;
}

QList<GameObject> *Snake::getParts(void) {
    return mSnakeParts;
}

QBrush Snake::colorize(int x, int y) {
    for (GameObject &obj : *mSnakeParts) {
        if (obj.intersects(x, y)) {
            return { "#00FF00" };
        }
    }
    return {"#000000"};
}
