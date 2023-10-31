//
// Created by esorochinskiy on 30.10.23.
//

#ifndef KQSNAKE_GAMEOBJECT_H
#define KQSNAKE_GAMEOBJECT_H


#include <QPoint>
#include <QBrush>

class GameObject : public QPoint {

public:
    GameObject(int, int, QBrush &);

    bool intersects(const GameObject &) const;
    bool intersects(int, int) const;
    QBrush &getColor();

private:
    QBrush mColor;
};


#endif //KQSNAKE_GAMEOBJECT_H
