import pygame


class Object(pygame.sprite.Sprite):
    def __init__(self, game, x=0, y=0, img=None):
        super().__init__()
        self.game = game
        self.image = img
        self.rect = self.image.get_rect()
        self.x, self.y = x, y

    def step(self):
        self.update()

    def update(self):
        pass

    @property
    def x(self):
        return self.rect.x + self.rect.width/2

    @x.setter
    def x(self, value):
        self.rect.x = value - self.rect.width/2

    @property
    def y(self):
        return self.rect.y + self.rect.height / 2

    @y.setter
    def y(self, value):
        self.rect.y = value - self.rect.height / 2
