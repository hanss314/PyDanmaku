import math


class Collider:
    """
    It can be rectangular or elliptical
    """
    def __init__(self, x, y, height, width, angle=0, ellipse=False):
        self.x, self.y = x, y
        self.height, self.width = height, width
        self.ellipse = ellipse
        self.angle = angle

    def collides(self, player) -> bool:
        # get all the points in the box
        halfbox = (player.hitbox - 1)/2
        player_box = [(player.x+x-halfbox, player.y+y-halfbox)
                      for x in range(player.hitbox) for y in range(player.hitbox)]

        # translate
        player_box = list(map(
            lambda pos: (pos[0] - self.x, pos[1] - self.y),
            player_box
        ))
        # rotate
        cos = math.cos(-self.angle)
        sin = math.sin(-self.angle)
        player_box = list(map(
            lambda pos: (pos[0]*cos - pos[1]*sin, pos[1]*cos + pos[0]*sin),
            player_box
        ))
        # scale
        player_box = list(map(
            lambda pos: (2 * pos[0] / self.width, 2 * pos[1] / self.height),
            player_box
        ))
        # test if in range
        if self.ellipse:
            return any(map(
                lambda pos: pos[0]**2 + pos[1]**2 <= 1, player_box
            ))
        else:
            return any(map(
                lambda pos: abs(pos[0]) <= 1 and abs(pos[1]) <= 1, player_box
            ))
