#!/usr/bin/env python3
import pydanmaku as pd
import random
import time
import math
from math import pi, sin, cos
from player import Moveable

#  import pkgutil
#  a =pkgutil.get_data('pydanmaku', 'shaders/frag.shader')
#  print(a)

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

x = pd.DanmakuGroup("images/rice.png")
y = pd.DanmakuGroup("images/amulet.png", True)
i = 0

#player = Moveable(100, 100, 2, "images/amulet.png")

violin_freqs = [
    0.995, 0.940, 0.425, 0.480, 0.0, 0.365, 0.040, 0.085, 0.0, 0.09
]

def violin(x):
    return sum (
        s*sin((n+1)*x) if n%2==0 else s*cos((n+1)*x)
        for n, s in enumerate(violin_freqs)
    )

@pd.modifier
def wavy(step, b):
    if b.life == 20:
        b = b._replace(angm=0.3)
    elif b.life >= t:
        b = b._replace(angm=0, ang=b.ang + 0.2*sin((step+b.life)/10))

    return b

t = 60

@pd.modifier
def stop(step, b):
    if b.life > 30:
        b = b._replace(speed=0, acc=0)
    return b

x.add_modifier(wavy)


"""
import matplotlib.pyplot as plt
ins = [2*pi*x/1000 for x in range(1001)]
outs = list(map(violin, ins))
plt.plot(ins, outs)
plt.show()

import sys
sys.exit(0)
"""
try:
    pd.init()
    start = time.time()
    i = 0
    pos = 100
    for _ in range(60000):
        i+=1
        
        if i % 120 == 1:
            t = random.randint(20, 80)
            for j in range(40):
                x.curvy_laser(
                    20*cos(i+pi*j/20), 20*sin(i+pi*j/20), True, 100, 15,
                    angle=i/30 + j*pi/20, speed=5
                )
        if i % 4 == 5:
            for j in range(10):
                y.add_bullet(
                    -pos+0*-100*violin(i/100), 0, False, 5, 100,
                    angle=2*pi*violin(i/100) + j*pi/5, speed=5
                )

        #player.run()
        x.run()
        x.render()
        y.run()
        y.render()
        keys = pd.get_keys()
        if keys[263]: pos += 2
        if keys[262]: pos -= 2
        pd.render()
        #framerate()

finally:
    pd.close()


