//
// Created by hanss on 10/31/18.
//
#include <list>
#include <string>

#include "../include/bullet.h"
#include "../include/group.h"

Group::Group(std::list<Bullet> bullet_list, std::string texture){
    this->bullet_list = bullet_list;
    this->texture = texture;
}
