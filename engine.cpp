#include "engine.hpp"
#include <cstddef>
#include <iostream>

void Engine::start() {
    if (!stopped) {
        throw "[FAIL]: trying to start the engine while it is already runnning";
    }

    std::cout << "[INFO]: Allegro is starting..." << std::endl;

    if (!al_init()) {
        throw "[FAIL]: allegro init";
    } else if (verbose) {
        std::cout << "[ OK ]: allegro init" << std::endl;
    }

    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        throw "[FAIL]: timer init";
    } else if (verbose) {
        std::cout << "[ OK ]: timer init" << std::endl;
    }

    display = al_create_display(WIDTH, HEIGHT);
    if (!display) {
        throw "[FAIL]: display init";
    } else if (verbose) {
        std::cout << "[ OK ]: display init" << std::endl;
    }

    if (!al_init_primitives_addon()) {
        throw "[FAIL]: primitives addons init";
    } else if (verbose) {
        std::cout << "[ OK ]: primitives addons init" << std::endl;
    }

    event_queue = al_create_event_queue();
    if (!event_queue) {
        throw "[FAIL]: event queue init";
    } else if (verbose) {
        std::cout << "[ OK ]: event queue init" << std::endl;
    }

    if (!al_install_keyboard()) {
        throw "[FAIL]: keyboard init";
    } else if (verbose) {
        std::cout << "[ OK ]: keyboard init" << std::endl;
    }

    if (!al_install_mouse()) {
        throw "[FAIL]: keyboard init";
    } else if (verbose) {
        std::cout << "[ OK ]: keyboard init" << std::endl;
    }

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    if (verbose) {
        std::cout << "[ OK ]: events are registered" << std::endl;
    }

    al_clear_to_color(bg_color);
    al_flip_display();
    al_start_timer(timer);
    std::size_t frame = 0;
    bool updated = false;
    stopped = false;
    if (verbose) {
        std::cout << "[ OK ]: engine set to initial state" << std::endl;
    }

    std::cout << "[INFO]: Allegro successefully started" << std::endl;
    if (verbose) {
        std::cout << "[ OK ]: game loop is about to begin" << std::endl;
    }

    forever {
        if (Engine::stopped) {
            break;
        }

        frame++;
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if (verbose) {
            std::cout << "[ OK ]: " << frame << " event" << std::endl;
        }

        switch (ev.type) {
        case ALLEGRO_EVENT_TIMER:
            updated = true;
            physics_process();
            if (verbose) {
                std::cout << "[ OK ]: " << frame << " physics" << std::endl;
            }
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            stop();
            return;
        }

        if (updated) {
            updated = false;
            if (full_redraw)
                al_clear_to_color(bg_color);
            render_process();
            al_flip_display();
            if (verbose) {
                std::cout << "[ OK ]: " << frame << " render" << std::endl;
            }
        }
    }
}

void Engine::stop() {
    std::cout << "[INFO]: Allegro stopping..." << std::endl;

    if (timer) {
        al_destroy_timer(timer);
        if (verbose)
            std::cout << "[ OK ]: timer destoryed" << std::endl;
    }

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

    Engine::stopped = true;

    std::cout << "[INFO]: Allegro was successefully stopped" << std::endl;
}