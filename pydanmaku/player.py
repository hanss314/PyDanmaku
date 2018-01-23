from .pdobject import Object


class Player(Object):
    def __init__(self, game, x=50, y=50, speed=10, img=''):
        super().__init__(game, x=x, y=y, img=img)
        self.game = game
        self.def_speed = speed
        self.speed = self.def_speed

    def up(self):
        self.rect.y -= self.speed

    def down(self):
        self.rect.y += self.speed

    def left(self):
        self.rect.x -= self.speed

    def right(self):
        self.rect.x += self.speed

    def shift(self):
        self.speed = self.def_speed / 2

    def unshift(self):
        self.speed = self.def_speed
