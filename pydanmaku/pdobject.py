import pygame


class Object(pygame.sprite.Sprite):
    def __init__(self, game, x=0, y=0, img=None):
        super().__init__()
        self.game = game
        self.image = img
        self.rect = self.image.get_rect()
        self.x, self.y = x, y
        self._x, self._y = x, y

    def step(self):
        """
        For safety reasons and future compatibility, do not override
        :return:
        """
        self.update()

    def update(self):
        """
        Overridable method that runs on every step
        :return:
        """
        pass

    @property
    def x(self):
        return self._x + self.rect.width/2

    @x.setter
    def x(self, value):
        self._x = value - self.rect.width/2
        self.rect.x = self._x

    @property
    def y(self):
        return self._y + self.rect.height / 2

    @y.setter
    def y(self, value):
        self._y = value - self.rect.height / 2
        self.rect.y = self._y
