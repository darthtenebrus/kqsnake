//
// Created by esorochinskiy on 30.10.23.
//

#include "gameobject.h"

GameObject::GameObject(int xpos, int ypos, QPixmap &image) :
                        QPoint(xpos, ypos) {
    mImg = image;

}

bool GameObject::intersects(const GameObject &other) const {
    return this->intersects(other.x(), other.y());
}

bool GameObject::intersects(int cx, int cy) const {
    return (this->x() == cx && this->y() == cy);
}

QPixmap &GameObject::getImg() {
    return mImg;
}
