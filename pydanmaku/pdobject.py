import pygame


class Object(pygame.sprite.Sprite):
    def __init__(self, game, x=0, y=0, img=None):
        super().__init__()
        self.game = game
        self.image = img
        self.image = pygame.image.load(img).convert()
        self.rect = self.image.get_rect()
        self.rect.x, self.rect.y = x, y

    def step(self):
        self.update()

    def update(self):
        pass

    def x(self):
        return self.rect.x

    def y(self):
        return self.rect.y
