#!/usr/bin/env python3
import pydanmaku as pd
from math import pi

groups = [pd.DanmakuGroup("images/amulet.png") for _ in range(10)]

for group in groups:
    for i in range(1000):
        group.add_bullet(0, 0, False, angle=i, speed=1)

try:
    pd.init()
    for _ in range(600):
        for group in groups:
            group.run()
            group.render()

        pd.render()


finally:
    pd.close()

