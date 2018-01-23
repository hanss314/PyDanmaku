from pygame import image, Rect


def load_image(fp):
    """
    Loads an image
    :param fp:
    :return pygame.Surface:
    """
    return image.load(fp).convert_alpha()


def load_image_chunks(fp, *chunks):
    """
    Loads an image and return the specified areas
    :param fp:
    :param chunks:
    :return [pygame.Surface]:
    """
    img = image.load(fp).convert_alpha()
    surfaces = []
    for chunk in chunks:
        surfaces.append(img.subsurface(Rect(*chunk)))

    return surfaces
