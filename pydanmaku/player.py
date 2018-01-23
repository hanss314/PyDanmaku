from .pdobject import Object


class Player(Object):
    def __init__(self, game, x=0, y=0, speed=10, img=None):
        super(Player, self).__init__(game, x=x, y=y, img=img)
        self.def_speed = speed
        self.speed = self.def_speed

    def up(self):
        self.y -= self.speed

    def down(self):
        self.y += self.speed

    def left(self):
        self.x -= self.speed

    def right(self):
        self.x += self.speed

    def shift(self):
        self.speed = self.def_speed / 2

    def unshift(self):
        self.speed = self.def_speed
