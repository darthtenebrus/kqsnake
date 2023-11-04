//
// Created by esorochinskiy on 30.10.23.
//

#include <QPainter>
#include "snake.h"
#include "constants.h"
#include "snakegame.h"

Snake::Snake(int x, int y) : QQueue<GameObject>() {
    mBody = QPixmap(":/images/body.png");
    for (int i = 2; i >= 0; i--) {
        enqueue(GameObject(x + i, y));
    }
    mDir = LEFT;
    mIsAlive = true;
}


void Snake::drawInitial(QPainter &painter) {
    Direction copyDir = getDirection();

    const QPixmap &cHead = QPixmap(":/images/head.png");
    for (GameObject &obj: *this) {
        int idx = indexOf(obj);
        if (idx != length() - 1) {
            const GameObject &prevObj = at(idx + 1);
            QPoint delta = obj - prevObj;
            if ((copyDir == LEFT || copyDir == RIGHT) && delta.y()) {
                copyDir = delta.y() > 0 ? UP : DOWN;
            } else if ((copyDir == UP || copyDir == DOWN) && delta.x()) {
                copyDir = delta.x() > 0 ? LEFT : RIGHT;
            }
        }

        QTransform rt;
        int iDir = static_cast<int>(copyDir);
        rt.rotate(iDir * 90);
        painter.drawPixmap(QRect(obj.x() * (MIN_CELL_SIZE), obj.y() * (MIN_CELL_SIZE),
                                 MIN_CELL_SIZE, MIN_CELL_SIZE), idx == length() - 1 ?
                                 cHead.transformed(rt) : QPixmap(":/images/body.png").transformed(rt));
    }
}

bool Snake::checkCollision(const GameObject &other) {
    return std::any_of(begin(), end(), [&](const GameObject &g) {
        return g.intersects(other);
    });
}


bool Snake::checkCollision(int x, int y) {
    return std::any_of(begin(), end(), [&](const GameObject &g) {
        return g.intersects(x, y);
    });
}

GameObject Snake::createNewHead() {
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

    return {newHeadX, newHeadY };
}

void Snake::removeTail() {
    if (!isEmpty()) {
        removeFirst();
    }
}

void Snake::move(SnakeGame *game) {
    GameObject newHead = createNewHead();
    int newHeadX = newHead.x();
    int newHeadY = newHead.y();
    if (newHeadX < 0 ||
        newHeadX >= game->getScreenCellsX() ||
        newHeadY < 0 ||
        newHeadY >= game->getScreenCellsY() ||
        checkCollision(newHead)) {
        mIsAlive = false;
    } else {
        enqueue(newHead);
        QList<GameObject> *apples = game->getApples();
        int i;
        if (std::any_of(apples->begin(), apples->end(), [&](GameObject &apple) {
            i = apples->indexOf(apple);
            return apple.intersects(newHead);
        })) {
            apples->removeAt(i);
        } else {
            removeTail();
        }
    }

}

bool Snake::isAlive() {
    return mIsAlive;
}

Snake::Direction &Snake::getDirection() {
    return mDir;
}

Snake::Direction &operator++(Snake::Direction &curr) {
    switch (curr) {
        case Snake::Direction::UP:
            curr = Snake::Direction::RIGHT;
            break;
        case Snake::Direction::RIGHT:
            curr = Snake::Direction::DOWN;
            break;
        case Snake::Direction::DOWN:
            curr = Snake::Direction::LEFT;
            break;
        case Snake::Direction::LEFT:
            curr = Snake::Direction::UP;
            break;

    }
    return curr;
}


Snake::Direction &operator--(Snake::Direction &curr) {
    switch (curr) {
        case Snake::Direction::UP:
            curr = Snake::Direction::LEFT;
            break;
        case Snake::Direction::LEFT:
            curr = Snake::Direction::DOWN;
            break;
        case Snake::Direction::DOWN:
            curr = Snake::Direction::RIGHT;
            break;
        case Snake::Direction::RIGHT:
            curr = Snake::Direction::UP;
            break;

    }
    return curr;
}