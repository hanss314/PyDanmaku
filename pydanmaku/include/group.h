//
// Created by hanss on 10/31/18.
//

#include <list>
#include <string>

#include <GL/glew.h>
#include "bullet.h"

#ifndef DANMAKU_GROUP_H
#define DANMAKU_GROUP_H

class Group : public Bullet{
public:
    std::list<Bullet> bullet_list;
    std::string texture;
    Group(std::list<Bullet>, std::string);

    void setSpeed(double);
};


#endif //DANMAKU_GROUP_H
