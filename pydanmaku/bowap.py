#!/usr/bin/env python3
import pydanmaku as pd
import random
import time
from math import pi, sin

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

x = pd.DanmakuGroup()
i = 0
try:
    pd.init()
    start = time.time()
    i = 0
    while True:
        i+=1
        for j in range(10):
            x.add_bullet(320, 240, False, 10, 15, 100*sin(i/400) + j*pi/5, 3, 0, 0.01)
        x.run()
        x.render()
        #framerate()

finally:
    pd.close()

