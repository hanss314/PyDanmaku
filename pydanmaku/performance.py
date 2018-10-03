#!/usr/bin/env python3
import danmaku
import random
import time
from math import pi, sin

"""
FPS = 60
wait = 1/FPS
previous = time.time()

def framerate():
    global previous, wait, FPS
    now = time.time()
    delta = now - previous
    to_wait = wait - delta
    previous = now + to_wait
    if to_wait < 0: return
    time.sleep(to_wait)
"""

x = danmaku.DanmakuGroup()
for i in range(100000):
    x.add_bullet(320, 400, True, 1, 1, i, 1, 0, 0.0)

try:
    danmaku.init()
    start = time.time()
    i = 0
    for i in range(600):
        x.run()
        x.render()
        #framerate()
    
    end = time.time()
    print(end-start)
finally:
    danmaku.close()

