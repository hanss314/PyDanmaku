//
// Created by hanss on 11/28/18.
//

#include <deque>
#include <tuple>
#include <string>

#ifndef DANMAKU_LASER_H
#define DANMAKU_LASER_H

#include "bullet.h"

extern void render_curvy(std::deque<std::tuple<double,double>>, std::string);

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
    bool run(double timestep, Bullet ref) override;
    bool run(double timestep) override;

    bool collides(double x, double y, double radius) override;
    void render(bool b, int i, double h, double w, std::string texture) override{
        render_curvy(this->positions, texture);
    }
};

#endif //DANMAKU_LASER_H
