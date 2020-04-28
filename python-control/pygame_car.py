import pygame
import mqtt_test as m
from pygame.locals import (
    RLEACCEL,
    K_SPACE,
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
    K_RETURN,
    KEYDOWN,
    QUIT   
)

SCREEN_WIDTH = 1280
SCREEN_HEIGHT = 720

log ='LOG'

print('Use arrowkeys to control car. SPACE to brake.\n ESC to exit')

class Player(pygame.sprite.Sprite):
    def __init__(self):
        super(Player, self).__init__()
        self.surf = pygame.image.load('pygame-mqtt-test/red_circle.png').convert()
        self.surf.set_colorkey((255,255,255), RLEACCEL)
        self.rect = self.surf.get_rect()
        self.rect.center = (SCREEN_WIDTH/2, SCREEN_HEIGHT/2)

    def update(self, pressed_keys):
        if pressed_keys[K_UP]:
            self.rect.center = (SCREEN_WIDTH/2, SCREEN_HEIGHT/2)
            self.rect.center = (SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 50)
            m.publish(msg='f1000')
        if pressed_keys[K_DOWN]:
            self.rect.center = (SCREEN_WIDTH/2, SCREEN_HEIGHT/2)
            self.rect.center = (SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 50)
            m.publish(msg='b1000')
        if pressed_keys[K_LEFT]:
            self.rect.center = (SCREEN_WIDTH/2, SCREEN_HEIGHT/2)
            self.rect.center = (SCREEN_WIDTH/2-50, SCREEN_HEIGHT/2)
            m.publish(msg='r90')
        if pressed_keys[K_RIGHT]:
            self.rect.center = (SCREEN_WIDTH/2, SCREEN_HEIGHT/2)
            self.rect.center = (SCREEN_WIDTH/2 + 50, SCREEN_HEIGHT/2)
            m.publish(msg='l90')
        if pressed_keys[K_SPACE]:
            self.rect.center = (SCREEN_WIDTH/2, SCREEN_HEIGHT/2)
            log = 'Stannad'
            m.publish(msg= 'f0')
        
            
pygame.init()

screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption('Car Controller')



player = Player()

all_sprites = pygame.sprite.Group()
all_sprites.add(player)

running = True
clock = pygame.time.Clock()

while running:
    for event in pygame.event.get():
        if event.type == KEYDOWN:
            if event.key == K_ESCAPE:
                running = False
            if event.key == K_UP:
                log = 'Framåt'
            if event.key == K_DOWN:
                log = 'Bakåt'
            if event.key == K_LEFT:
                log = 'Vänster'
            if event.key == K_RIGHT:
                log = 'Höger'
            if event.key == K_SPACE:
                log = 'Stannad'
        
        elif event.type == QUIT:
            running = False

    pressed_keys = pygame.key.get_pressed()
    player.update(pressed_keys)

    screen.fill((200,200,200))
    font = pygame.font.Font('freesansbold.ttf', 18)
    text = font.render(log , True, (255,255,255), (0,0,0))
    textRect = text.get_rect()
    textRect.center = (SCREEN_WIDTH/2, SCREEN_HEIGHT*0.8)
    screen.blit(text, textRect)

    Surf = pygame.Surface((300,300))
    Surf.fill((20,20,20))
    Surf_center = (
        (SCREEN_WIDTH-Surf.get_width())/2,
        (SCREEN_HEIGHT-Surf.get_height())/2
    )
    screen.blit(Surf, Surf_center)

    for entity in all_sprites:
        screen.blit(entity.surf, entity.rect)
    
    pygame.display.flip()
    clock.tick(30)

m.client.disconnect()