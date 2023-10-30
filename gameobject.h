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

    bool intersects(GameObject &);
    bool intersects(int, int);
    QBrush &getColor(void);

private:
    QBrush mColor;
};


#endif //KQSNAKE_GAMEOBJECT_H
