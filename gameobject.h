//
// Created by esorochinskiy on 30.10.23.
//

#ifndef KQSNAKE_GAMEOBJECT_H
#define KQSNAKE_GAMEOBJECT_H


#include <QPoint>

class GameObject : public QPoint {

public:
    GameObject(int xpos, int ypos);

    bool intersects(GameObject &);
    bool intersects(int, int);


};


#endif //KQSNAKE_GAMEOBJECT_H
