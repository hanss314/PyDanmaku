#!/usr/bin/env python3
import pydanmaku as pd


x = pd.DanmakuGroup("images/rice.png")
for i in range(10000):
    x.add_bullet(0, 0, False, angle=i, speed=0.2)


try:
    pd.init()
    for _ in range(600):
        x.run()
        x.render()
        pd.render()


finally:
    pd.close()

