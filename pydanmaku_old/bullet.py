import math
import pygame

from .pdobject import Object
from .collider import Collider

from math import radians as rads
from math import degrees as degs


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
        self.stop_in = -1
        self.pattern = []
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
        if self.pattern:
            self.run_pattern()
        if self.stop_in > 0:
            self.stop_in -= 1
        elif self.stop_in == 0:
            self.speed = 0

        super().step()

    def run_pattern(self):
        nxt = self.pattern[0]
        if 'wait' in nxt:
            nxt['wait'] -= 1

        if 'wait' not in nxt or nxt['wait'] <= 0:
            nxt = self.pattern.pop(0)
            for name in ['x', 'y', 'vx', 'vy', 'speed', 'angle']:
                if name in nxt:
                    setattr(self, name, nxt[name])

            if 'exec' in nxt:
                args = nxt['args'] if 'args' in nxt else ()
                kwargs = nxt['kwargs'] if 'kwargs' in nxt else {}
                nxt['exec'](*args, **kwargs)

    def move_to(self, x, y, frames=0):
        """
        Move to a point over a certain number of frames
        :param x:
        :param y:
        :param frames:
        :return:
        """
        if frames != 0:
            self.vx = (x - self.x) / frames
            self.vy = (y - self.y) / frames
            self.stop_in = frames
        else:
            self.x, self.y = x, y

    def point_towards(self, obj):
        """
        Set the bullet to point towards an object
        :param obj:
        :return:
        """
        self.angle = math.atan2(self.y - obj.y, self.x - obj.x)

    @property
    def speed(self):
        return math.sqrt(self.vx**2 + self.vy**2)

    @speed.setter
    def speed(self, value):
        self.angle = degs(math.atan2(self.vy, self.vx)) + (180 if self.vx < 0 else 0)
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
