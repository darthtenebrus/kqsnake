//
// Created by esorochinskiy on 30.10.23.
//

#ifndef KQSNAKE_GAMEOBJECT_H
#define KQSNAKE_GAMEOBJECT_H


#include <QPoint>
#include <QBrush>

class GameObject : public QPoint {

public:
    GameObject(int, int, QPixmap &);

    bool intersects(const GameObject &) const;
    bool intersects(int, int) const;
    QPixmap &getImg();

private:
    QPixmap mImg;
};


#endif //KQSNAKE_GAMEOBJECT_H
