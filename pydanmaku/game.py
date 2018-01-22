import pygame
import inspect


class Game:
    def __init__(self):
        self.screen = pygame.display.set_mode((640, 480), pygame.FULLSCREEN)
        self.tasks = []
        self.objects = []

    def run(self):
        while True:
            for obj in list(self.objects):
                if hasattr(obj, 'step'):
                    obj.step()
                if hasattr(obj, 'should_remove') and obj.should_remove:
                    self.objects.remove(obj)

            for task in list(self.tasks):
                try:
                    task.__next__()
                except StopIteration:
                    self.tasks.remove(task)

            pygame.display.update()

    def add_task(self, task):
        if not inspect.isgenerator(task):
            raise ValueError('Object must be a generator')
        self.tasks.append(task)
