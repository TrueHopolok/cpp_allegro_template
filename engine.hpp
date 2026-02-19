#ifndef ENGINE
#define ENGINE

#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <allegro5/display.h>
#include <allegro5/events.h>
#include <allegro5/keyboard.h>
#include <allegro5/mouse.h>
#include <allegro5/system.h>
#include <allegro5/timer.h>
#include <cstddef>
#include <functional>

#define forever while (true)

class Engine {
  private:
    Engine() {};
    Engine(const Engine &) {};
    Engine(Engine &&) noexcept {};
    static bool stopped;

  public:
    static const std::size_t FPS = 60;
    static const std::size_t WIDTH = 640;
    static const std::size_t HEIGHT = 360;
    static const bool VERBOSE = true;
    static constexpr ALLEGRO_COLOR BG_COLOR = {0, 0, 0, 0};

    static bool paused;
    static ALLEGRO_TIMER *timer;
    static ALLEGRO_DISPLAY *display;
    static ALLEGRO_EVENT_QUEUE *event_queue;

    static void start(const std::function<void()> &fps_update,
                      const std::function<void()> &draw_update);
    static void stop();
};

#endif