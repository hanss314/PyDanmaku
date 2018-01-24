import pygame
import inspect


PRESSED = {
    pygame.K_UP: 'up',
    pygame.K_DOWN: 'down',
    pygame.K_LEFT: 'left',
    pygame.K_RIGHT: 'right',
}

DOWN = {
    pygame.K_LSHIFT: 'shift',
}

UP = {
    pygame.K_LSHIFT: 'unshift',
}


class Game:
    def __init__(self):
        self.screen = pygame.display.set_mode((640, 480))
        self.tasks = []
        self.objects = pygame.sprite.Group()
        self.player = pygame.sprite.Group()

    def run(self):
        """
        Start the game
        :return:
        """
        clock = pygame.time.Clock()
        while True:
            clock.tick(60)
            self.screen.fill((255, 255, 255))
            # self.objects.clear(self.screen)
            self.objects.draw(self.screen)
            for task in list(self.tasks):
                try:
                    task.__next__()
                except StopIteration:
                    self.tasks.remove(task)
            keys = pygame.key.get_pressed()
            events = pygame.event.get()
            for obj in self.objects:
                for event in events:
                    if event.type == pygame.KEYDOWN and event.key in DOWN and hasattr(obj, DOWN[event.key]):
                        obj.__getattribute__(DOWN[event.key])()
                    elif event.type == pygame.KEYUP and event.key in UP and hasattr(obj, UP[event.key]):
                        obj.__getattribute__(UP[event.key])()

                for k, v in PRESSED.items():
                    if keys[k] and hasattr(obj, v):
                        obj.__getattribute__(v)()

            for obj in list(self.objects.sprites()):
                if hasattr(obj, 'step'):
                    obj.step()
                if hasattr(obj, 'should_remove') and obj.should_remove:
                    self.objects.remove(obj)

            pygame.display.update()

    def add_task(self, task):
        """
        Adds a task to be run.
        :param task:
        :return:
        """
        if not inspect.isgenerator(task):
            raise ValueError('Object must be a generator')
        self.tasks.append(task)

    def set_player(self, player):
        if self.player.sprites():
            self.player.sprites()[0].kill()
        self.player.add(player)
        self.objects.add(player)


    def add_bullet(self, bullet):
        print(bullet)
        self.objects.add(bullet)
