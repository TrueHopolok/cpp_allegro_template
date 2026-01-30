# Туториал по установке С++ и Allegro5

Тут полный туториал как установить плюсы как на `Windows` так и на `Linux` + установка `Allegro5` в `Codeblocks` и в `VScode`.
Также тут есть мини гайд как работать с `Codeblocks` совсем в краце. 

Актуален на момент `31.01.2026` для версий `codeblocks 25.03` и `allegro 5.2.11.2`.

## Windows + Codeblocks

В этой главе описана как установка, так и краткое руководство по использованию.

### Установка среды разработки

1) Скачать `Codeblocks` по ссылке: https://sourceforge.net/projects/codeblocks/files/Binaries/25.03/Windows/codeblocks-25.03-setup.exe/download.

2) Установить `Codeblocks` и запустить. Он уже должен работать для `C` и `C++` файлов. Для проверки можно написать Hello world! программу.

    ```c++
    #include <iostream>

    using namespace std;

    int main() {
        cout << "Hello world!" << endl;
    }
    ```

3) Скачать `Allegro5` по ссылке: https://github.com/liballeg/allegro5/releases/download/5.2.11.2/allegro-x86_64-w64-mingw32-gcc-15.2.0-posix-seh-dynamic-5.2.11.2.zip.

4) Разархивировать в любую директорию (желательно отдельно от рабочей директории).

5) Далее надо залинковать `Codeblocks` с `Allegro5`:

    1) `Settings -> Compiler -> Linker Settings`.

    2) Добавьте файлы: 
        - `allegro/lib/liballegro.dll.a`;
        - `allegro/lib/liballegro_main.dll.a`;
        - `allegro/lib/liballegro_primitives.dll.a`.
    
    3) Из `Linker Settings` надо перейти в `Search directories`.

    4) Добавить директорию: `allegro/include`.

Готово далее смотреть: базовый проект по `Allegro5`.

### Краткое руководство по работе с Codeblocks

В Codeblocks-е можно работать как с одиночными файлами, так и с проектами.

В любом из случаев - запуск программы можно сделать нажав зелённую стрелочку с шестерёнкой либо нажав `F9`.

#### Одиночные файлы

- Создание: `File->New->Empty File` + `Ctrl+S` сохранить как `.cpp` файл.
- Открытие: `File->Open` и выберите свой файл.

#### Проекты

- Создание: `File->New->Project->Empty Project`, далее кликнуть `Next` и выбрать название проекта и где он хранится. Нажать `Next` и `Finish`. Готово.
- Открытие: `File->Open` и выбрать `.cbp` файл.
- Добавить/удалить файлы: ПКМ по иконке проекта в `Codeblocks` слева в файловой системе. Далее будет выбор какие файлы добавить или удалить. Все файлы должны быть в директории проекта или под-директории проекта.

## Windows + VScode

1) Скачать и установить компилятор `С++`. 
    - Можно установить по этому гайду: https://code.visualstudio.com/docs/languages/cpp.
    - Можно просто скачать `Codeblocks` и вместе с этим скачается и компилятор, который далее надо просто добавить в `%PATH%` в Windows-e.
    
2) Проверить работает ли комиплятор можно выполнив команду `g++ --version`. Далее запуск программ можно воспроизводить с помощью `g++ main.cpp -o progam`, где 
    - `main.cpp` - исполнимый файл;
    - `program` - название сбилденого файла.

3) Скачать `Allegro5` по ссылке: https://github.com/liballeg/allegro5/releases/download/5.2.11.2/allegro-x86_64-w64-mingw32-gcc-15.2.0-posix-seh-dynamic-5.2.11.2.zip.

4) Разархивировать в рабочую директорию проекта для более лёгкого линка. Далее компиляция любого проекта происходит так (для переноса строки используйте `^` в `cmd` или `\` в `bash`):
    ```
    g++ main.cpp -o program 
    -Iallegro/include -Lallegro/lib -lallegro -lallegro_main -lallegro_primitives
    ```

## Linux

1) Скачать `C++` с помощью команд:
    ```sh
    sudo apt update
    sudo apt-get install g++
    ```
    Проверить можно так: `g++ --version`.

2) Скачать `Allegro5` можно выполнив 1-2 команды из гайда по ссылке: https://github.com/liballeg/allegro_wiki/wiki/Quickstart#ubuntu-1804-or-derivatives-thereof.

3) Запуск проекта с `Allegro5` можно сделать с помощью этой команды:
    ```sh
    g++ main.cpp -o linux/app \
    $(pkg-config --cflags --libs allegro-5 allegro_primitives-5)
    ```

## Базовый проект по Allegro5

После установки, скопируйте код ниже и скомпилируйте.

Файл `example_1.cpp`:
```c++
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <cstdio>

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 32;

int main(int argc, char **argv)
{
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *bouncer = NULL;
    float bouncer_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
    float bouncer_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;
    float bouncer_dx = -4.0, bouncer_dy = 4.0;
    bool redraw = true;

    if (!al_init())
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    if (!timer)
    {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }

    display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display)
    {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_timer(timer);
        return -1;
    }

    bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
    if (!bouncer)
    {
        fprintf(stderr, "failed to create bouncer bitmap!\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    al_set_target_bitmap(bouncer);

    al_clear_to_color(al_map_rgb(255, 0, 255));

    al_set_target_bitmap(al_get_backbuffer(display));

    event_queue = al_create_event_queue();
    if (!event_queue)
    {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_bitmap(bouncer);
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_flip_display();

    al_start_timer(timer);

    while (1)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            if (bouncer_x < 0 || bouncer_x > SCREEN_W - BOUNCER_SIZE)
            {
                bouncer_dx = -bouncer_dx;
            }

            if (bouncer_y < 0 || bouncer_y > SCREEN_H - BOUNCER_SIZE)
            {
                bouncer_dy = -bouncer_dy;
            }

            bouncer_x += bouncer_dx;
            bouncer_y += bouncer_dy;

            redraw = true;
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }

        if (redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;

            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);

            al_flip_display();
        }
    }

    al_destroy_bitmap(bouncer);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
```

После компиляции программа будет вылетать с ошибкой. Её надо поместить в одну директорию с `.dll` файлами из `allegro/bin`. Можно либо его руками переносить, либо перенести все `.dll` файлы в директорию к исполняемому файлу.

Для примера `Codeblocks` компилирует проект по `bin/Debug` пути относительно `.cbp` файла. Можно перенести все `.dll` файлы в эту директорию, чтобы после не думать об этом.

Для тех кто пользуется другим редактором, можно в аргументе компиляции указать путь, куда сохранятеся исполняемый файл. Например будет `bin` директория. Тогда можно перенести все `.dll` файлы туда и запустить компиляцию с флагом `-o bin/program`.