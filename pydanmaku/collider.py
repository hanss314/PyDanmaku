import math

from math import radians as rads
from math import degrees as degs


class Collider:
    """
    It can be rectangular or elliptical
    """
    def __init__(self, x, y, height, width, angle=0, ellipse=False):
        self.x, self.y = x, y
        self.height, self.width = height, width
        self.ellipse = ellipse
        self.angle = angle

    def collides_player(self, player) -> bool:
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

    def get_axis(self, x, y, angle) -> (int, int):
        """
        Returns the range of coverage along a line.
        Part of Seperated Axis Theorem
        :param x:
        :param y:
        :param angle:
        :return:
        """
        # Finds distance from axis "center" to our center
        # Puts axis "center" on origin, rotates our center, then takes x value
        mx = self.x - x
        my = self.y - y
        center = mx * math.cos(rads(-angle)) - my * math.sin(rads(-angle))

        # Reduce angle to equivalent case between 0 and 90 degrees
        # Rotates by 180 degrees because rotational symmetry of lines
        # then mirrors across x-axis if needed
        # This is the angle between collider and axis
        angle = (self.angle % 180) - (angle % 180)
        if angle < 0: angle = -angle
        if angle > 90: angle = 180 - angle

        if self.ellipse:
            # Uses the derivative of ellipse, dy/dx = (height**2) / (width ** 2) * x / y
            coefficient = -self.height * self.height / (self.width * self.width)
            # Finds slope we need: (dy/dx), then finds the x/y value needed
            slope = math.tan(rads(angle - 90))
            slope /= coefficient
            # calculus and algebra to find the y coordinate
            py = self.height * self.width
            py *= math.sqrt(
                1/(slope * slope * self.height * self.height + self.width * self.width)
            ) / 2
            px = slope * py
            # The angle between collider and our point
            diangle = degs(math.atan2(py, px))
            angle -= diangle
            distance = math.hypot(py, px) * math.cos(rads(angle))

        else:
            # Take the diagonal of one of the quadrants, from the center to the farthest corner
            # Since we transformed it, only one corner can be the farthest
            diagonal = math.hypot(self.width, self.height) / 2
            diangle = degs(math.atan2(self.height, self.width))
            # Angle(collider, axis) - Angle(collider, diagonal) = Angle(diagonal, axis)
            angle -= diangle
            distance = diagonal * math.cos(rads(angle))

        # It should always be positive, but just to make sure
        distance = abs(distance)
        return center - distance, center + distance

    def collides(self, collider) -> bool:
        """
        Returns if a collider is intersecting another
        :param collider:
        :return:
        """
        max_dist = math.hypot(
            (self.width + collider.width) / 2,
            (self.height + collider.height) / 2
        )

        if max_dist < math.hypot(self.x - collider.x, self.y - collider.y):
            return False

        check_ellipse = self.ellipse or collider.ellipse
        lines = {self.angle, self.angle+90, collider.angle, collider.angle+90}
        if check_ellipse:
            lines.add(degs(
                math.atan2(self.y-collider.y, self.x-collider.x)
            ))

        def overlap(angle):
            angle %= 360
            # get their coverage on the axis
            # the first return value will always be smaller
            al, ah = self.get_axis(self.x, self.y, angle)
            bl, bh = collider.get_axis(self.x, self.y, angle)
            # test if they overlap
            c = al <= bh and bl <= ah
            return c

        return all(map(
            overlap, lines
        ))
