//
// Created by esorochinskiy on 30.10.23.
//

#ifndef KQSNAKE_GAMEOBJECT_H
#define KQSNAKE_GAMEOBJECT_H


#include <QPoint>
#include <QBrush>

class GameObject : public QPoint {


public:
    enum ItemType {
        ItemAny = 0,
        ItemApple,
        ItemMalus
    };

    GameObject(int, int, ItemType=ItemAny);

    bool intersects(const GameObject &) const;
    bool intersects(int, int) const;

    ItemType getItemType() const;

private:
    ItemType mItemType;
};


#endif //KQSNAKE_GAMEOBJECT_H
