#!/usr/bin/env python3
import pydanmaku as pd
import random
import time
import math
from math import pi, sin, cos

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

x = pd.DanmakuGroup("images/amulet.png")
y = pd.DanmakuGroup("images/rice.png")
i = 0

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
    b = b._replace(ang=b.ang + 0.07*sin((step+b.life)/20), acc=b.acc+0.001)
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
    for _ in range(60000):
        i+=1
        if i % 4 == 1:
            for j in range(10):
                x.add_bullet(
                    100+0*100*violin(i/100), 0, True, 10, 15,
                    angle=i/30 + j*pi/5, speed=5
                )
        if i % 4 == 3:
            for j in range(10):
                y.add_bullet(
                    -100+0*-100*violin(i/100), 0, False, 10, 15,
                    angle=2*pi*violin(i/100) + j*pi/5, speed=5
                )
        x.run()
        x.render()
        y.run()
        y.render()
        pd.render()
        #framerate()

finally:
    pd.close()


