#include <stdbool.h>
#include <math.h>
#include <cstdio>
#include <iostream>
#include "bullet.h"

bool Bullet::run(double timestep){
    last_x = x;
    last_y = y;
    speed += acceleration * timestep;
    angle += angular_momentum * timestep;
    angle = fmod(angle, (double) M_PIl * 2);
    this->s = sinf(angle);
    this->c = cosf(angle);
    x += this->c * speed * timestep;
    y += this->s * speed * timestep;
    //return false;
    return x < -10 || x > 650 || y < -10 || y > 490;
}

bool Bullet::broad_search(double x, double y, double radius){
    double dx = x - this->x, dy = y - this->y;
    return sqrt(dx*dx + dy*dy) <= radius + this->radius;
}

bool Bullet::collides(double x, double y, double radius){
    if (!this->broad_search(x, y, radius)) return false;

    // transform to 0,0
    x -= this->x;
    y -= this->y;

    // transform so rotation is 0
    // normal equation is x = xcos - ysin; y = xsin + ycos
    // we're reversing the rotation, cos(-a) = cos(a), sin(-a) = -sin(a)
    // equation becomes x = xcos + ysin; y = ycos-xsin
    double tx = x*this->c + y*this->s;
    double ty = y*this->c - x*this->s;

    // move into one quadrant
    if (tx < 0) tx = -tx;
    if (ty < 0) ty = -ty;

    // extents in quadrant
    double w = this->width/2, h = this->height/2;

    if (this->is_rect) {
        // is it intersecting the top or right?
        if ((tx + radius <= w && ty <= h) || (ty + radius <= h && tx <= w)) return true;
        // find distance from corner and test if intersecting corner
        double dx = tx - h, dy = tx - w;
        return sqrt(dx * dx + dy * dy) <= radius;
    } else {
        // extend ellipse by radius of circle
        // will test if the centre of the circle is within the bigger ellipse
        w += radius; h += radius;
        // transform to a unit circle
        x /= w; y /= h;
        // if we're within the unit circle, we were within the bigger ellipse
        return sqrt(x*x + y*y) <= 1;
    }


}

Bullet:: Bullet(
    double x, double y, bool is_rect, double width, double height,
    double speed, double angle, double accel, double ang_m
){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    if (is_rect) {
        this->radius = sqrt(width * width + height * height);
    } else if (width > height){
        this->radius = width;
    } else {
        this->radius = height;
    }
    this->is_rect = is_rect;
    this->speed = speed;
    this->angle = fmod(angle, 2*M_PI);
    this->acceleration = accel;
    this->angular_momentum = ang_m;
}


