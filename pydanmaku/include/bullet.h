#include <stdbool.h>
#ifndef DANMAKU_H
#define DANMAKU_H

class Bullet {
public:
    double last_x;
    double last_y;
    double x;
    double y;
    double angle;
    double speed;
    double acceleration;
    double angular_momentum;
    bool is_rect;
    double height;
    double width;
    double radius;
    double c, s; // cos and sin

    bool broad_search(double x, double y, double radius);
    bool collides(double x, double y, double radius);

    Bullet(double x, double y, bool is_rect, double width, double height, double speed, double angle, double accel, double ang_m);
    bool run(double timestep);

};

#endif