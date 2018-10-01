#include <stdbool.h>
#include <math.h>
#include <cstdio>
#include "bullet.h"

bool Bullet::run(float timestep){
    last_x = x;
    last_y = y;
    speed += acceleration * timestep;
    angle += angular_momentum * timestep;
    angle = fmod(angle, (float) M_PIl * 2);
    x += cosf(angle) * speed * timestep;
    y += sinf(angle) * speed * timestep;
    if (x < -10 || x > 650 || y < -10 || y > 490) return true;
    return false;
}


Bullet::Bullet(float x, float y, float radius){
    Bullet(x, y, radius, 0.0f, 0.0f);
}

Bullet::Bullet(float x, float y, float width, float height){
    Bullet(x, y, width, height, 0.0f, 0.0f);
}

Bullet::Bullet(float x, float y, float radius, float speed, float angle){
    Bullet(x, y, radius, speed, angle, 0.0f, 0.0f);
}
Bullet::Bullet(float x, float y, float width, float height, float speed, float angle){
    Bullet(x, y, width, height, speed, angle, 0.0f, 0.0f);
}

Bullet::Bullet(
        float x, float y, float radius,
        float speed, float angle, float accel, float ang_m
){
    this->x = this->last_x = x;
    this->y = this->last_y = y;
    this->radius = radius;
    this->width = this->height = radius;
    this->is_rect = false;
    this->speed = speed;
    this->angle = angle;
    this->acceleration = accel;
    this->angular_momentum = ang_m;
}

Bullet:: Bullet(
    float x, float y, float width, float height,
    float speed, float angle, float accel, float ang_m
){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->radius = sqrtf(width*width + height*height);
    this->is_rect = true;
    this->speed = speed;
    this->angle = angle;
    this->acceleration = accel;
    this->angular_momentum = ang_m;
}


