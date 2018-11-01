#!/usr/bin/env python3
import pydanmaku as pd
from math import pi

x = pd.DanmakuGroup("images/rice.png")

try:
    pd.init()
    for i in range(600000):
        if i%10 == 0:
            x.add_bullet(0, 0, angle=0, speed=1, angular_momentum=-0.01)
            x.add_bullet(0, 0, angle=pi, speed=1, angular_momentum=-0.01)

        x.run()
        x.render()
        pd.render()

finally:
    pd.close()


