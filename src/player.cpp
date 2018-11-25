//
// Created by hanss on 11/25/18.
//
#include "../include/player.h"

Player::Player(double x, double y, double r, char* texture){
    this->x = x;
    this->y = y;
    this->r = r;
    this->texture = texture;
    this->angle = 0.;
}