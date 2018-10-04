#!/usr/bin/env python3
import danmaku
import random
import time
from math import pi, sin, atan2, cos, hypot

FPS = 60
wait = 1/FPS
previous = time.time()

def framerate():
    global previous, wait, FPS
    now = time.time()
    delta = now - previous
    to_wait = wait - delta
    previous += wait
    if to_wait < 0:
        print('bad'); return
    time.sleep(to_wait)

manager = danmaku.DanmakuGroup()
i = 0
try:
    danmaku.init()
    start = time.time()
    i = 0
    x, y = 320, 400
    nx, ny = x, y
    print("hi")
    while True:
        i+=1
        if i%2 == 0: 
            for j in range(8):
                if i > 100:
                    manager.add_bullet(x, y, True, 1, 1, i/30+j*pi/4, 4, 0.0)
                manager.add_bullet(x, y, True, 1, 1, -i/21+j*pi/4, 2.1, 0.0)

        if i%150 == 0:
            nx = random.randint(max(100, x-50), min(540, x+50))
            ny = random.randint(max(350, y-50), min(450, y+50))

        a = atan2(ny-y, nx-x)
        dist = hypot(ny-y, nx-x)
        x += cos(a)*min(dist, 1)
        y += sin(a)*min(dist, 1)
        manager.run()
        manager.render()
        #framerate()

finally:
    danmaku.close()

