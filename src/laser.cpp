//
// Created by hanss on 11/28/18.
//

#include "../include/laser.h"
#include "../include/renderer.h"

bool CurvyLaser::run(double timestep, Bullet ref) {
    printf("curvy run\n");
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
    printf("curvy run\n");
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
