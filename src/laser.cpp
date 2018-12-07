//
// Created by hanss on 11/28/18.
//

#include <tuple>
#include <math.h>
#include "../include/laser.h"
#include "../include/renderer.h"

bool CurvyLaser::run(double timestep, Bullet ref) {
    Bullet::run(timestep, ref);
    std::tuple<double,double> position = std::make_tuple(this->x,this->y);
    this->positions.push_front(position);
    if (this->positions.size() > height){
        positions.pop_back();
    }
    position = positions.back();
    double x = std::get<0>(position);
    double y = std::get<1>(position);

    return x < -10 || x > 650 || y < -10 || y > 490;
}

bool CurvyLaser::run(double timestep) {
    Bullet::run(timestep);
    std::tuple<double,double> position = std::make_tuple(this->x,this->y);
    this->positions.push_front(position);
    if (this->positions.size() > height){
        positions.pop_back();
    }
    position = positions.back();
    double x = std::get<0>(position);
    double y = std::get<1>(position);

    return x < -10 || x > 650 || y < -10 || y > 490;
}

bool boxcollides(
    double x1, double y1,
    double x2, double y2, 
    double w,
    double x, double y,
    double radius
){
    double ang = atan2(y2-y1, x2-x1);
    double h = hypot(y2-y1, x2-x1);
    double mx = (x1+x2)/2, my = (y1+y2)/2;
    x -= mx; y -= my;
    double c = cos(ang), s = sin(ang);
    double tx = mx*c + my*s;
    double ty = my*c - mx*s;
    if (tx < 0) tx = -tx;
    if (ty < 0) ty = -ty;
    h /= 2; w /= 2;

    if ((tx + radius <= w && ty <= h) || (ty + radius <= h && tx <= w)) return true;
    double dx = tx - h, dy = tx - w;
    return sqrt(dx * dx + dy * dy) <= radius;
}


bool CurvyLaser::collides(double x, double y, double radius){
    for (int i=0; i<(int)this->positions.size()-1; i++){
        std::tuple<double,double> fst = this->positions[i];
        std::tuple<double,double> snd = this->positions[i+1];
        if (boxcollides(
            std::get<0>(fst), std::get<1>(fst),
            std::get<0>(snd), std::get<1>(snd),
            this->height, x, y, radius
        )){return true;}
    }
    return false;
}

