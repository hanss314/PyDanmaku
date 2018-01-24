import math

from .pdobject import Object


def rads(number):
    return math.pi * number / 180


class Bullet(Object):
    def __init__(
            self, game, x=0, y=0, img=None, *,
            vx=None, vy=None, speed=None, angle=None, acceleration=0, angular_momentum=0
    ):
        super().__init__(game, x=x, y=y, img=img)
        self.vx = vx or 0
        self.vy = vy or 0
        self._angle = angle or 0  # cache in case speed drops to 0
        self.acceleration = acceleration
        self.angular_momentum = angular_momentum
        if angle is not None and speed is not None:
            self.speed = speed

    def step(self):
        self.speed += self.acceleration
        self.angle += self.angular_momentum
        self.angle %= 360
        self.x += self.vx
        self.y += self.vy
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

    @angle.setter
    def angle(self, value):
        self._angle = value
        self.vx = math.cos(rads(self._angle)) * self.speed
        self.vy = math.sin(rads(self._angle)) * self.speed
