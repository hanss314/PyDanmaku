import pygame


class Object(pygame.sprite.Sprite):
    def __init__(self, game, x=0, y=0, img=None, collider=None):
        super().__init__()
        self.rect = img.get_rect()
        self._x, self._y = x, y
        self.x, self.y = x, y
        self.game = game
        self.image = img
        self.collider = collider

    def step(self):
        """
        For safety reasons and future compatibility, do not override
        :return:
        """
        self.collider.x, self.collider.y = self.x, self.y
        self.update()

    def update(self):
        """
        Overridable method that runs on every step
        :return:
        """
        pass

    @property
    def x(self):
        return self._x

    @x.setter
    def x(self, value):
        self._x = value
        self.rect.centerx = self._x

    @property
    def y(self):
        return self._y

    @y.setter
    def y(self, value):
        self._y = value
        self.rect.centery = self._y
