import pygame

WIDTH = 800
HIGHT = 600

pygame.init()
display = pygame.display.set_mode((WIDTH, HIGHT))
spritesheet_view_surface = pygame.Surface((WIDTH // 2, HIGHT // 2))
spritesheet_view_scroll = [0, 0]
spritesheet_view_scroll_start = (0, 0)
spritesheet_view_scroll_end = (0, 0)
font = pygame.font.Font(None, 21)
texturepaths = [
    "../assets/neo_zero_tileset_02.png",
    "../assets/neo_zero_props_02_free.png"
]
textures = [pygame.image.load(t).convert_alpha() for t in texturepaths]
textureScale = 1
dragging = False
start_pos = (0, 0)
current_rect = pygame.Rect(0, 0, 0, 0)
CTRL_ = False


def eventhandler():
    global textureScale, dragging, current_rect, start_pos, CTRL_
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            quit()
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                quit()
            elif event.key == pygame.K_RCTRL or event.key == pygame.K_LCTRL:
                CTRL_ = True
        elif event.type == pygame.KEYUP:
            if event.key == pygame.K_RCTRL or event.key == pygame.K_LCTRL:
                CTRL_ = False
        elif event.type == pygame.MOUSEWHEEL:
            if event.y > 0:
                textureScale *= 1.1
            elif event.y < 0:
                textureScale /= 1.1
            textureScale = max(1, min(textureScale, 10))
        elif event.type == pygame.MOUSEBUTTONDOWN:
            if (not CTRL_):
                dragging = True
                start_pos = event.pos
                current_rect = pygame.Rect(start_pos, (0, 0))
        elif event.type == pygame.MOUSEMOTION and dragging:
            if (not CTRL_):
                end_pos = event.pos
                current_rect.width = end_pos[0] - start_pos[0]
                current_rect.height = end_pos[1] - start_pos[1]
        elif event.type == pygame.MOUSEBUTTONUP:
            if (not CTRL_):
                dragging = False
                current_rect.normalize()


def runmain():
    while True:
        eventhandler()
        mouse = pygame.mouse.get_pos()
        if (CTRL_):
            spritesheet_view_scroll[0] = mouse[0]
        display.fill("#151515")
        spritesheet_view_surface.fill("#000000")
        y = 0
        for t in textures:
            original_width, original_height = t.get_size()
            new_size = (
                int(original_width * textureScale),
                int(original_height * textureScale)
            )
            t_scaled = pygame.transform.scale(t, new_size)
            spritesheet_view_surface.blit(
                t_scaled,
                (
                    0 + spritesheet_view_scroll[0],
                    y + spritesheet_view_scroll[1]
                )
            )
            y += t.get_height() * textureScale

        display.blit(spritesheet_view_surface, (10, 10))
        text_surface = font.render(
            f"x: {mouse[0]}, y: {mouse[1]}",
            True,
            (200, 200, 200)
        )
        pygame.draw.rect(display, (255, 0, 0), current_rect, 1)
        display.blit(text_surface, (5, HIGHT - text_surface.get_height() - 5))
        pygame.display.update()


if __name__ == "__main__":
    runmain()
