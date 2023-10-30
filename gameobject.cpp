//
// Created by esorochinskiy on 30.10.23.
//

#include "gameobject.h"

GameObject::GameObject(int xpos, int ypos) : QPoint(xpos, ypos) {

}

bool GameObject::intersects(GameObject &other) {
    return this->intersects(other.x(), other.y());
}

bool GameObject::intersects(int cx, int cy) {
    return (this->x() == cx && this->y() == cy);
}
