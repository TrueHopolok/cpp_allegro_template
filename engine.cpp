#include "engine.hpp"
#include <iostream>

ALLEGRO_EVENT_QUEUE *Engine::event_queue = nullptr;
ALLEGRO_DISPLAY *Engine::display = nullptr;
ALLEGRO_TIMER *Engine::timer = nullptr;

bool Engine::stopped = true;
bool Engine::paused = false;

void Engine::start(const std::function<void()> &fps_update,
                   const std::function<void()> &draw_update) {
    if (!stopped) {
        throw "[FAIL]: trying to start the engine while it is already runnning";
    }

    std::cout << "[INFO]: Allegro is starting..." << std::endl;

    if (!al_init()) {
        throw "[FAIL]: allegro init";
    } else if (Engine::VERBOSE) {
        std::cout << "[ OK ]: allegro init" << std::endl;
    }

    timer = al_create_timer(1.0 / (double)Engine::FPS);
    if (!timer) {
        throw "[FAIL]: timer init";
    } else if (Engine::VERBOSE) {
        std::cout << "[ OK ]: timer init" << std::endl;
    }

    display = al_create_display(Engine::WIDTH, Engine::HEIGHT);
    if (!display) {
        throw "[FAIL]: display init";
    } else if (Engine::VERBOSE) {
        std::cout << "[ OK ]: display init" << std::endl;
    }

    if (!al_init_primitives_addon()) {
        throw "[FAIL]: primitives addons init";
    } else if (Engine::VERBOSE) {
        std::cout << "[ OK ]: primitives addons init" << std::endl;
    }

    event_queue = al_create_event_queue();
    if (!event_queue) {
        throw "[FAIL]: event queue init";
    } else if (Engine::VERBOSE) {
        std::cout << "[ OK ]: event queue init" << std::endl;
    }

    if (!al_install_keyboard()) {
        throw "[FAIL]: keyboard init";
    } else if (Engine::VERBOSE) {
        std::cout << "[ OK ]: keyboard init" << std::endl;
    }

    if (!al_install_mouse()) {
        throw "[FAIL]: keyboard init";
    } else if (Engine::VERBOSE) {
        std::cout << "[ OK ]: keyboard init" << std::endl;
    }

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    if (Engine::VERBOSE) {
        std::cout << "[ OK ]: events are registered" << std::endl;
    }

    al_clear_to_color(Engine::BG_COLOR);
    al_flip_display();
    al_start_timer(timer);

    if (Engine::VERBOSE) {
        std::cout << "[ OK ]: engine set to initial state" << std::endl;
    }

    bool updated = false;
    Engine::stopped = false;
    Engine::paused = false;

    std::cout << "[INFO]: Allegro successefully started" << std::endl;

    forever {
        if (Engine::stopped) {
            break;
        } else if (Engine::paused) {
            continue;
        }

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        switch (ev.type) {
        case ALLEGRO_EVENT_TIMER:
            updated = true;
            if (fps_update)
                fps_update();
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            Engine::stop();
            return;
        }

        if (updated) {
            updated = false;
            al_clear_to_color(Engine::BG_COLOR);
            if (draw_update)
                draw_update();
            al_flip_display();
        }
    }
}

void Engine::stop() {
    std::cout << "[INFO]: Allegro stopping..." << std::endl;

    if (timer) {
        al_destroy_timer(timer);
        if (Engine::VERBOSE)
            std::cout << "[ OK ]: timer destoryed" << std::endl;
    }

    if (display) {
        al_destroy_display(display);
        if (Engine::VERBOSE)
            std::cout << "[ OK ]: display destoryed" << std::endl;
    }

    if (event_queue) {
        al_destroy_event_queue(event_queue);
        if (Engine::VERBOSE)
            std::cout << "[ OK ]: event queue destoryed" << std::endl;
    }

    Engine::stopped = true;

    std::cout << "[INFO]: Allegro was successefully stopped" << std::endl;
}