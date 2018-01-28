import math
import pygame

from .pdobject import Object
from .collider import Collider

from math import radians as rads


class Bullet(Object):
    def __init__(
            self, game, x=0, y=0, img=None, *,
            vx=None, vy=None, speed=None, angle=None, acceleration=0, angular_momentum=0,
            collider=None
    ):
        super().__init__(game, x=x, y=y, img=img, collider=collider)
        self.vx = vx or 0
        self.vy = vy or 0
        self._angle = angle or 0  # cache in case speed drops to 0
        self.acceleration = acceleration
        self.angular_momentum = angular_momentum
        self.base_image = self._image = img
        if angle is not None and speed is not None:
            self.speed = speed

        if not collider:
            self.collider = Collider(self.x, self.y, self.rect.height, self.rect.width, self.angle)

    def step(self):
        self.speed += self.acceleration
        self.angle += self.angular_momentum
        self.angle %= 360
        self.x += self.vx
        self.y += self.vy
        self.image = pygame.transform.rotate(self.base_image, -self.angle)
        self.collider.x, self.collider.y = self.x, self.y
        super().step()

    @property
    def speed(self):
        return math.sqrt(self.vx**2 + self.vy**2)

    @speed.setter
    def speed(self, value):
        self.vx = math.cos(rads(self._angle)) * value
        self.vy = math.sin(rads(self._angle)) * value

    @property
    def angle(self):
        return self._angle

    @property
    def image(self):
        return self._image

    @image.setter
    def image(self, value):
        x, y = self.x, self.y
        self._image = value
        self.rect = self._image.get_rect()
        self.x = x
        self.y = y

    @angle.setter
    def angle(self, value):
        self._angle = value
        self.collider.angle = self.angle
        self.vx = math.cos(rads(self._angle)) * self.speed
        self.vy = math.sin(rads(self._angle)) * self.speed
