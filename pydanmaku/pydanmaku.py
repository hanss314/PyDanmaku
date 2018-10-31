from __future__ import annotations
from typing import List

import _pydanmaku as pd
from _pydanmaku import *


class DanmakuGroup(pd._DanmakuGroup):
    subgroups: List[DanmakuGroup]
    texture: str

    def __init__(self, texture=''):
        super().__init__(texture)
        self.subgroups = []
        self.texture = texture

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

    def run(self):
        super()._run()
        for group in self.subgroups:
            group.run()

    def add_bullet(
            self, x, y, is_rect=True,
            height=0, width=0, radius=None,
            angle=0, speed=0, acceleration=0, angular_momentum=0
    ):
        if radius is not None:
            height = width = radius

        super()._add_bullet(x, y, is_rect, height, width, angle, speed, acceleration, angular_momentum)


