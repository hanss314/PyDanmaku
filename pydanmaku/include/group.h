//
// Created by hanss on 10/31/18.
//

#include <list>
#include <string>

#include <GL/glew.h>

#ifndef DANMAKU_GROUP_H
#define DANMAKU_GROUP_H

class Group {
public:
    std::list<Bullet> bullet_list;
    std::string texture;



    Group(std::list<Bullet>, std::string);
};

#endif //DANMAKU_GROUP_H
