# ALLEGRO GUIDE

## DRAW

### Primitives
```c++
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

al_draw_line(x1, y1, x2, y2, color, thickness);

al_draw_rectangle(x1, y1, x2, y2, color, thickness);
al_draw_filled_rectangle(x1, y1, x2, y2, color);

al_draw_circle(cx, cy, radius, color, thickness);
al_draw_filled_circle(cx, cy, radius, color);

al_draw_triangle(x1,y1, x2,y2, x3,y3, color, thickness);
al_draw_filled_triangle(x1,y1, x2,y2, x3,y3, color);

al_draw_ellipse(cx, cy, rx, ry, color, thickness);
al_draw_filled_ellipse(cx, cy, rx, ry, color);

// Those 2 functions are handled automaticly by `engine.cpp` 
al_clear_to_color(0, 0, 0); // fill the screen in black color
al_flip_display(); // update whole screen to the latest version
```

### Colors
```c++
#include <allegro5/color.h>

ALLEGRO_COLOR color = al_map_rgb(0, 0, 0); // black
ALLEGRO_COLOR color = al_map_rgb(255, 255, 255); // white
ALLEGRO_COLOR color = al_map_rgba(0, 0, 0, 0); // black non-transperent
ALLEGRO_COLOR color = al_map_rgba(0, 0, 0, 128); // black half-transperent
ALLEGRO_COLOR color = {0, 0, 0, 0}; // black non-transperent
ALLEGRO_COLOR color = {255, 255, 255, 128}; // white half-transperent
```

## INPUT

### Keyboard input
```c++
#include <allegro5/keyboard.h>
#include <allegro5/keycodes.h>

ALLEGRO_KEYBOARD_STATE state;
al_get_keyboard_state(&state);
al_key_down(&state, ALLEGRO_KEY_SPACE); // return bool
```

### Mouse input
```c++
#include <allegro5/mouse.h>

ALLEGRO_MOUSE_STATE state;
al_get_mouse_state(&state);
al_mouse_button_down(&mstate, ALLEGRO_MOUSE_BUTTON_MIDDLE); // return bool
state.x, state.y; // position of the mouse on the screen
```