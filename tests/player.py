#!/usr/bin/env python3
import pydanmaku as pd
import random
import time
import math
from math import pi, sin, cos
from pydanmaku.enums import *


FPS = 60
wait = 1/FPS
previous = time.time()

class Moveable(pd.Player):
    def __init__(self, *args):
        super().__init__(*args)

    def step(self):
        x, y = self.get_pos()
        keys = pd.get_keys()
        if keys[KEY_UP]: y += 3
        if keys[KEY_DOWN]: y -= 3
        if keys[KEY_RIGHT]: x += 3
        if keys[KEY_LEFT]: x -= 3
        self.set_pos(x, y)

    def collision(self):
        print('Collision!')


if __name__ == '__main__':
    x = Moveable(100, 100, 1, "images/amulet.png")
    try:
        pd.init()
        for _ in range(60000):
            pd.render()
            #framerate()

    finally:
        del x
        pd.close()


