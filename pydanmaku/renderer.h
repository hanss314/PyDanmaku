#include <list>
#include "bullet.h"
#ifndef DANMAKU_RENDERER_H
#define DANMAKU_RENDERER_H
void renderer_init();
void render_bullets(std::list<Bullet> *bullets);
void renderer_close();
#endif //DANMAKU_RENDERER_H
