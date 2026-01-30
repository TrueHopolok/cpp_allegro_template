#ifndef ALLEGROUTIL_HPP_INCLUDED
#define ALLEGROUTIL_HPP_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

extern ALLEGRO_DISPLAY *alDisplay;
extern ALLEGRO_EVENT_QUEUE *alEventQueue;
extern ALLEGRO_TIMER *alTimer;

typedef void (*FpsCallback)();
typedef void (*DrawCallback)();

bool InitAllegro(int screenWidth, int screenHeight, int fps);
void DestroyAllegro();
void RunAllegro(FpsCallback fpsCallback, DrawCallback drawCallback);
void ExitAllegro();

#endif // ALLEGROUTIL_HPP_INCLUDED