#include <stdbool.h>

#ifndef DANMAKU_H
#define DANMAKU_H

extern void add_quad(int, double, double, double, double, double);

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
    bool _is_curvy = false;
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

    virtual ~Bullet(){};
    virtual bool run(double);
    virtual bool run(double, Bullet);
    virtual void del(){};
    virtual void render(bool is_laser, int i, double h, double w) {
        if (is_laser){
            add_quad(i, this->x, this->y, this->height, this->width, this->angle);
        } else {
            add_quad(i, this->x, this->y, h, w, this->angle);
        }
    };

};

#endif
