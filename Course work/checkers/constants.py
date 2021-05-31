import pygame

WIDTH, HEIGHT = 800, 800
ROWS, COLS = 8, 8
SQUARE_SIZE = WIDTH//COLS

# rgb
RED = (166, 20, 0)
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
BLUE = (0, 0, 255)
GREY = (128,128,128)
TREE = (255, 219, 160)

CROWN = pygame.transform.scale(pygame.image.load('assets/crown.png'), (55, 35))
