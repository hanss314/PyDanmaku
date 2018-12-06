#include <list>
#include <deque>
#include "bullet.h"
#include <FreeImage.h>
#include <GL/glew.h>

#include "player.h"
#include "group.h"

#define INPUT_COUNT 512

#ifndef DANMAKU_RENDERER_H
#define DANMAKU_RENDERER_H


void renderer_init(const char* directory);
void render_bullets(Group *group);
void render_player(Player *player);
void renderer_close();
void renderer_draw();
int* get_keys();
void add_quad(int, double, double, double, double, double);
void render_curvy(std::deque<std::tuple<double,double>>, std::string);
#endif //DANMAKU_RENDERER_H
