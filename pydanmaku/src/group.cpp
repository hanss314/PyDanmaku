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
    this->x = this->lx = 320.0;
    this->y = this->ly = 240.0;

    this->c = this->lc = 1.0;
    this->s = this->ls = 0.0;
    this->angle = this->la = 0.0;

    this->speed = 0;
    this->acceleration = 0;
    this->angular_momentum = 0;
}

