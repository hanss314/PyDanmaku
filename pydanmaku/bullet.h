#include <stdbool.h>
#ifndef DANMAKU_H
#define DANMAKU_H

class Bullet {
public:
    float last_x;
    float last_y;
    float x;
    float y;
    float angle;
    float speed;
    float acceleration;
    float angular_momentum;
    bool is_rect;
    float height;
    float width;
    float radius;

    Bullet() {};
    Bullet(float x, float y, float radius);
    Bullet(float x, float y, float width, float height);
    Bullet(float x, float y, float radius, float speed, float angle);
    Bullet(float x, float y, float width, float height, float speed, float angle);
    Bullet(float x, float y, float radius, float speed, float angle, float accel, float ang_m);
    Bullet(float x, float y, float width, float height, float speed, float angle, float accel, float ang_m);
    bool run(float timestep);

};

#endif