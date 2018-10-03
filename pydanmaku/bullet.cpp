#include <stdbool.h>
#include <math.h>
#include <cstdio>
#include "bullet.h"

bool Bullet::run(double timestep){
    last_x = x;
    last_y = y;
    speed += acceleration * timestep;
    angle += angular_momentum * timestep;
    angle = fmod(angle, (double) M_PIl * 2);
    x += cosf(angle) * speed * timestep;
    y += sinf(angle) * speed * timestep;
    //return false;
    return x < -10 || x > 650 || y < -10 || y > 490;
}


Bullet::Bullet(double x, double y, double radius){
    Bullet(x, y, radius, 0.0f, 0.0f);
}

Bullet::Bullet(double x, double y, double width, double height){
    Bullet(x, y, width, height, 0.0f, 0.0f);
}

Bullet::Bullet(double x, double y, double radius, double speed, double angle){
    Bullet(x, y, radius, speed, angle, 0.0f, 0.0f);
}
Bullet::Bullet(double x, double y, double width, double height, double speed, double angle){
    Bullet(x, y, width, height, speed, angle, 0.0f, 0.0f);
}

Bullet::Bullet(
        double x, double y, double radius,
        double speed, double angle, double accel, double ang_m
){
    this->x = this->last_x = x;
    this->y = this->last_y = y;
    this->radius = radius;
    this->width = this->height = radius;
    this->is_rect = false;
    this->speed = speed;
    this->angle = fmod(angle, 2*M_PI);
    this->acceleration = accel;
    this->angular_momentum = ang_m;
}

Bullet:: Bullet(
    double x, double y, double width, double height,
    double speed, double angle, double accel, double ang_m
){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->radius = sqrt(width*width + height*height);
    this->is_rect = true;
    this->speed = speed;
    this->angle = fmod(angle, 2*M_PI);
    this->acceleration = accel;
    this->angular_momentum = ang_m;
}


