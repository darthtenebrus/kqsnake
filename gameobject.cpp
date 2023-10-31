//
// Created by esorochinskiy on 30.10.23.
//

#include "gameobject.h"

GameObject::GameObject(int xpos, int ypos, QBrush &color) :
                        QPoint(xpos, ypos) {
    mColor = color;

}

bool GameObject::intersects(const GameObject &other) const {
    return this->intersects(other.x(), other.y());
}

bool GameObject::intersects(int cx, int cy) const {
    return (this->x() == cx && this->y() == cy);
}

QBrush &GameObject::getColor() {
    return mColor;
}
