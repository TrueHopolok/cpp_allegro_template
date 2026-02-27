#include "engine.hpp"
#include <iostream>
#include <stdexcept>

void Engine::start() {
    if (!stopped) {
        throw std::logic_error(
            "[FAIL]: trying to start the engine while it is already runnning");
    }

    std::cout << "[INFO]: Allegro is starting..." << std::endl;

    if (!Engine::initialized) {
        Engine::initialized = true;

        if (!al_init()) {
            throw std::runtime_error("[FAIL]: allegro init");
        } else if (verbose) {
            std::cout << "[ OK ]: allegro init" << std::endl;
        }

        if (!al_init_primitives_addon()) {
            throw std::runtime_error("[FAIL]: primitives addon init");
        } else if (verbose) {
            std::cout << "[ OK ]: primitives addons init" << std::endl;
        }

        if (!al_install_keyboard()) {
            throw std::runtime_error("[FAIL]: keyboard init");
        } else if (verbose) {
            std::cout << "[ OK ]: keyboard init" << std::endl;
        }

        if (!al_install_mouse()) {
            throw std::runtime_error("[FAIL]: keyboard init");
        } else if (verbose) {
            std::cout << "[ OK ]: keyboard init" << std::endl;
        }

        if (!al_init_image_addon()) {
            throw std::runtime_error("[FAIL]: images addon init");
        } else if (verbose) {
            std::cout << "[ OK ]: images addon init" << std::endl;
        }

        if (!al_init_font_addon() || !al_init_ttf_addon()) {
            throw std::runtime_error("[FAIL]: text addon init");
        } else if (verbose) {
            std::cout << "[ OK ]: text addon init" << std::endl;
        }
    }

    timer = al_create_timer(1.0 / (double)Engine::FPS);
    if (!timer) {
        throw std::runtime_error("[FAIL]: timer init");
    } else if (verbose) {
        std::cout << "[ OK ]: timer init" << std::endl;
    }

    display = al_create_display(Engine::WIDTH, Engine::HEIGHT);
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

    forever {
        if (stopped) {
            if (verbose)
                std::cout << "[ OK ]: engine was stopped manually" << std::endl;
            return;
        }

        frame++;
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        switch (ev.type) {
        case ALLEGRO_EVENT_TIMER:
            updated = true;
            physics_process();
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            if (verbose)
                std::cout << "[ OK ]: close event on frame " << frame
                          << std::endl;
            stop();
            return;
        }

        if (updated) {
            updated = false;
            if (full_redraw)
                al_clear_to_color(bg_color);
            render_process();
            al_flip_display();
        }
    }
}

void Engine::stop() {
    std::cout << "[INFO]: Allegro is stopping..." << std::endl;

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

    stopped = true;

    std::cout << "[INFO]: Allegro was successefully stopped" << std::endl;
}