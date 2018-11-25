#include <stdbool.h>
#ifndef DANMAKU_H
#define DANMAKU_H

class Bullet {
public:
    double x;
    double y;
    double angle;
    double speed;
    double acceleration;
    double angular_momentum;
    bool is_rect;
    bool _ref_applied = false;
    double height;
    double width;
    double radius;
    double c, s; // cos and
    double lx, ly, la, lc, ls; //previous state
    int life=0;

    bool broad_search(double x, double y, double radius);
    bool collides(double x, double y, double radius);

    Bullet();
    Bullet(
        double x, double y, bool is_rect,
        double width, double height,
        double speed, double angle,
        double accel, double ang_m
    );
    bool run(double);
    bool run(double, Bullet);

};

#endif