//
// Created by hanss on 11/25/18.
//
#include <string>

#ifndef DANMAKU_PLAYER_H
#define DANMAKU_PLAYER_H
class Player {
public:
    double x;
    double y;
    double r;
    double angle;
    std::string texture;
    Player(double x, double y, double r, char* texture);
};

#endif //DANMAKU_PLAYER_H
