#include <list>
#include "bullet.h"
#include <FreeImage.h>
#include <GL/glew.h>

#include "../include/group.h"

#define INPUT_COUNT 512

#ifndef DANMAKU_RENDERER_H
#define DANMAKU_RENDERER_H


void renderer_init();
void render_bullets(Group *group);
void renderer_close();
void renderer_draw();
int* get_keys();
#endif //DANMAKU_RENDERER_H
