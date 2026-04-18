#include "engine.hpp"
#include "allegro5/altime.h"
#include "allegro5/events.h"
#include <iostream>
#include <stdexcept>

Engine::Engine(int display_width, int display_height, double frames_per_second,
               bool enable_verbose_mode) {
    if (display_width <= 0) {
        throw std::invalid_argument("[FAIL]: display width must be positive");
    }
    width = display_width;

    if (display_height <= 0) {
        throw std::invalid_argument("[FAIL]: display height must be positive");
    }
    height = display_height;

    if (frames_per_second <= 0.0) {
        throw std::invalid_argument(
            "[FAIL]: frames per second must be positive");
    }
    fps = frames_per_second;

    verbose = enable_verbose_mode;

    Engine::initialize_allegro(enable_verbose_mode);
}

void Engine::initialize_allegro(bool verbose_output) {
    std::lock_guard<std::mutex> init_lock_gurad(init_lock);

    if (Engine::initialized) {
        if (verbose_output) {
            std::cout << "[INFO]: Allegro was initialized" << std::endl;
        }
        return;
    }
    std::cout << "[INFO]: Allegro is initializing..." << std::endl;

    if (!al_init()) {
        throw std::runtime_error("[FAIL]: allegro init");
    } else if (verbose_output) {
        std::cout << "[ OK ]: allegro init" << std::endl;
    }

    if (!al_init_primitives_addon()) {
        throw std::runtime_error("[FAIL]: primitives addon init");
    } else if (verbose_output) {
        std::cout << "[ OK ]: primitives addons init" << std::endl;
    }

    if (!al_install_keyboard()) {
        throw std::runtime_error("[FAIL]: keyboard init");
    } else if (verbose_output) {
        std::cout << "[ OK ]: keyboard init" << std::endl;
    }

    if (!al_install_mouse()) {
        throw std::runtime_error("[FAIL]: keyboard init");
    } else if (verbose_output) {
        std::cout << "[ OK ]: keyboard init" << std::endl;
    }

    if (!al_init_image_addon()) {
        throw std::runtime_error("[FAIL]: images addon init");
    } else if (verbose_output) {
        std::cout << "[ OK ]: images addon init" << std::endl;
    }

    if (!al_init_font_addon() || !al_init_ttf_addon()) {
        throw std::runtime_error("[FAIL]: text addon init");
    } else if (verbose_output) {
        std::cout << "[ OK ]: text addon init" << std::endl;
    }

    if (verbose_output) {
        std::cout << "[INFO]: Allegro was initialized" << std::endl;
    }
    Engine::initialized = true;
}

const ALLEGRO_DISPLAY *Engine::get_display() { return display; }

void Engine::start() {
    if (!stopped) {
        throw std::logic_error(
            "[FAIL]: trying to start the engine while it is already runnning");
    }

    std::cout << "[INFO]: Engine is starting..." << std::endl;

    display = al_create_display(width, height);
    if (!display) {
        throw std::runtime_error("[FAIL]: display init");
    } else if (verbose) {
        std::cout << "[ OK ]: display init" << std::endl;
    }

    event_queue = al_create_event_queue();
    if (!event_queue) {
        throw std::runtime_error("[FAIL]: event queue init");
    } else if (verbose) {
        std::cout << "[ OK ]: event queue init" << std::endl;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    if (verbose) {
        std::cout << "[ OK ]: events are registered" << std::endl;
    }

    al_clear_to_color(bg_color);
    al_flip_display();
    frame = 0;
    stopped = false;
    update_time = al_get_time();
    if (verbose) {
        std::cout << "[ OK ]: engine set to initial state" << std::endl;
    }

    std::cout << "[INFO]: Engine successefully started" << std::endl;

    forever {
        if (!cycle()) {
            return;
        }
    }
}

bool Engine::cycle() {
    if (stopped) {
        if (verbose)
            std::cout << "[ OK ]: engine was stopped manually" << std::endl;
        return false;
    }

    double start_time = al_get_time();

    ALLEGRO_EVENT ev;
    while (al_get_next_event(event_queue, &ev)) {
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            stop();
            return false;
        }
    }

    double current_time = al_get_time();
    process(current_time - update_time);
    al_clear_to_color(bg_color);
    render();
    al_flip_display();
    update_time = current_time;
    frame++;

    double remainding_time = (1.0 / fps) - (al_get_time() - start_time);
    if (remainding_time > 0.0) {
        al_wait_for_event_timed(event_queue, &ev, remainding_time);
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            stop();
            return false;
        }
    }
    return true;
}

void Engine::stop() {
    std::cout << "[INFO]: Engine is stopping..." << std::endl;

    if (display) {
        al_destroy_display(display);
        if (verbose)
            std::cout << "[ OK ]: display destoryed" << std::endl;
    }

    if (event_queue) {
        al_destroy_event_queue(event_queue);
        if (verbose)
            std::cout << "[ OK ]: event queue destoryed" << std::endl;
    }

    stopped = true;

    std::cout << "[INFO]: Engine was successefully stopped" << std::endl;
}