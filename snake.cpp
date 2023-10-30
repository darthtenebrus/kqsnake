//
// Created by esorochinskiy on 30.10.23.
//

#include "snake.h"

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
