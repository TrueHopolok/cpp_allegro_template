#ifndef ENGINE
#define ENGINE

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/altime.h>
#include <allegro5/color.h>
#include <allegro5/events.h>
#include <allegro5/keyboard.h>
#include <allegro5/mouse.h>
#include <allegro5/system.h>
#include <mutex>

#define forever while (true)

class Engine {
  private:
    // Removed constructors to not mess with internal params
    // and allegro initiazation states
    Engine() = delete;
    Engine(const Engine &) = delete;
    Engine &operator=(const Engine &) = delete;
    Engine(Engine &&) = delete;
    Engine &operator=(Engine &&) = delete;

    // Fields required for global initialization of Allegro module
    static inline std::mutex init_lock;
    static inline bool initialized = false;
    static void initialize_allegro(bool verbose_output);

    // Internal params that are not for manual usage
    bool cycle();
    int frame;
    double update_time;
    bool stopped = true;
    ALLEGRO_DISPLAY *display = nullptr;
    ALLEGRO_EVENT_QUEUE *event_queue = nullptr;

  protected:
    // Function to get access to display.
    // May be useful for internal systems,
    // but should be limited for outside modifications.
    const ALLEGRO_DISPLAY *get_display();

    // Engine's update rate in frames per second
    double fps;

    // Display's width
    int width;

    // Display's height
    int height;

    // TRUE: outputs debug info into console
    bool verbose;

    // Color that fills the screen before `render`
    ALLEGRO_COLOR bg_color = {0, 0, 0, 0};

    // Called each frame to update internal logic
    virtual void process(double delta_time) = 0;

    // Called each frame to redraw all things on screen
    virtual void render() = 0;

    // Initialize Allegro if needed.
    // Then create engine instance.
    Engine(int display_width, int display_height, double frames_per_second,
           bool enable_verbose_mode);

    // Virtual, since it is a requirement for abstract classes
    virtual ~Engine() = default;

  public:
    // Starts the game loop
    void start();

    // Stops running game loop
    void stop();
};

#endif