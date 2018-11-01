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
    /*
    this->angle = this->la = 1;
    this->angular_momentum = 0.01;
    */
    this->c = this->lc = 1.0;
    this->s = this->ls = 0.0;
    this->angle = this->la = 0.0;

}

void Group::setSpeed(double speed) {
    this->speed = speed;
}
