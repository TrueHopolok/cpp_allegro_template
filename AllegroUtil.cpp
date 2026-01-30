#include "AllegroUtil.hpp"
#include <iostream>

using namespace std;

int alFps;
ALLEGRO_DISPLAY *alDisplay = 0;
ALLEGRO_EVENT_QUEUE *alEventQueue = 0;
ALLEGRO_TIMER *alTimer = 0;

// local data
bool alExit = false;

bool InitAllegro(int screenWidth, int screenHeight, int fps)
{
    alFps = fps;
    if (!al_init())
    {
        cout << "failed to initialize allegro!" << endl;
        return false;
    }

    alTimer = al_create_timer(1.0 / alFps);
    if (!alTimer)
    {
        cout << "failed to create timer!" << endl;
        return false;
    }

    alDisplay = al_create_display(screenWidth, screenHeight);
    if (!alDisplay)
    {
        cout << "failed to create display!" << endl;
        return false;
    }

    if (!al_init_primitives_addon())
    {
        cout << "failed to init addons!" << endl;
        return false;
    }

    alEventQueue = al_create_event_queue();
    if (!alEventQueue)
    {
        cout << "failed to create event queue!" << endl;
        return false;
    }

    al_register_event_source(alEventQueue, al_get_display_event_source(alDisplay));
    al_register_event_source(alEventQueue, al_get_timer_event_source(alTimer));

    alExit = false;

    return true;
}

void DestroyAllegro()
{
    if (alTimer)
    {
        al_destroy_timer(alTimer);
    }

    if (alDisplay)
    {
        al_destroy_display(alDisplay);
    }

    if (alEventQueue)
    {
        al_destroy_event_queue(alEventQueue);
    }
}

void RunAllegro(FpsCallback fpsCallback, DrawCallback drawCallback)
{
    // clear screen
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    al_start_timer(alTimer);

    bool redraw = false;
    while (true)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(alEventQueue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            if (fpsCallback)
            {
                fpsCallback();
            }
            redraw = true;
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }

        if (redraw && al_is_event_queue_empty(alEventQueue))
        {
            redraw = false;
            if (drawCallback)
            {
                drawCallback();
            }
            al_flip_display();
        }

        if (alExit)
        {
            break;
        }
    }
}

void ExitAllegro()
{
    alExit = true;
}
