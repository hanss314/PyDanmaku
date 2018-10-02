#include <list>
#include "bullet.h"
#include <FreeImage.h>
#include <GL/glew.h>

#ifndef DANMAKU_RENDERER_H
#define DANMAKU_RENDERER_H



void renderer_init();
void render_bullets(std::list<Bullet> *bullets);
void renderer_close();
#endif //DANMAKU_RENDERER_H
