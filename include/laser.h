//
// Created by hanss on 11/28/18.
//

#include <deque>
#include <tuple>

#ifndef DANMAKU_LASER_H
#define DANMAKU_LASER_H

#include "bullet.h"

extern void render_curvy(std::deque<std::tuple<double,double>>);

class CurvyLaser : public Bullet{
public:
    CurvyLaser(
            double x, double y, bool is_rect, double width, double height,
            double speed, double angle, double accel, double ang_m
    ) : Bullet(x, y, is_rect, width, height, speed, angle, accel, ang_m) {
        this->_is_curvy = true;
    }
    ~CurvyLaser(){ this->positions.clear(); }
    std::deque<std::tuple<double,double>> positions;
    void del() override{
    //      this->positions.clear();
    }
    bool run(double timestep, Bullet ref);
    void render(bool b, int i, double h, double w) override{
        render_curvy(this->positions);
    }
};

#endif //DANMAKU_LASER_H
