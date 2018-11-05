from __future__ import annotations
from typing import List, Callable
from collections import namedtuple

import _pydanmaku as pd
from _pydanmaku import *


Bullet = namedtuple('Bullet', ['life', 'x', 'y', 'ang', 'lx', 'ly', 'la', 'speed', 'acc', 'angm'])



def modifier(f: Callable[[int, Bullet], Bullet]) -> \
        Callable[[int], Callable[[Bullet], Bullet]]:

    def wrapper(step: int):
        def actual_modifier(bullet: Bullet):
            return f(step, bullet)
        return actual_modifier
    return wrapper


class DanmakuGroup(pd._DanmakuGroup):
    subgroups: List[DanmakuGroup]
    texture: str
    step: int
    modifiers: List[Callable[[int], Callable[[Bullet], Bullet]]]

    def __init__(self, texture=''):
        super().__init__(texture)
        self.subgroups = []
        self.texture = texture
        self.step = 0
        self.modifiers = []

    def add_modifier(self, f: Callable[[int], Callable[[Bullet], Bullet]]):
        self.modifiers.append(f)

    def render(self):
        self._render()
        for group in self.subgroups:
            group.render()

    def add_group(self, group: DanmakuGroup):
        if not group.texture and self.texture:
            group.set_texture(self.texture)
        self.subgroups.append(group)

    def set_texture(self, texture: str):
        self.texture = texture
        self._set_texture(texture)

    def run(self, parent=None):
        for modifier in self.modifiers:
            super()._run_modifier(Bullet, modifier(self.step))
        if parent is None:
            super()._run()
        else:
            super()._run(parent)
        for group in self.subgroups:
            group.run(self)

        self.step += 1

    def add_bullet(
            self, x, y, is_rect=True,
            height=0, width=0, radius=None,
            angle=0, speed=0, acceleration=0, angular_momentum=0
    ):
        if radius is not None:
            height = width = radius

        super()._add_bullet(x, y, is_rect, height, width, angle, speed, acceleration, angular_momentum)


