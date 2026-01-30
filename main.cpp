#include <iostream>
#include "AllegroUtil.hpp"
// #include <windows.h> // used on Windows operating system
#include <cstdlib>
#include <cstdio>

using namespace std;

const int FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;

int i = 0;
void draw1()
{
    ++i;
    cout << "frame " << i << endl;

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_put_pixel(0, 0, al_map_rgb(0, 255, 0));
    al_draw_line(100, 100, 300, 200, al_map_rgb(255, 0, 0), 5);
    al_draw_triangle(120, 120, 150, 120, 130, 150, al_map_rgb(255, 0, 0), 3);
    al_draw_filled_triangle(120, 220, 150, 220, 130, 250, al_map_rgb(0, 255, 0));
    al_draw_rectangle(300, 300, 350, 350, al_map_rgb(0, 255, 0), 1);
    al_draw_filled_rectangle(350, 300, 400, 350, al_map_rgb(0, 255, 255));
    al_draw_circle(500, 400, 50, al_map_rgb(0, 255, 0), 3);
    al_draw_filled_circle(400, 400, 50, al_map_rgb(0, 255, 255));
}

void draw2()
{
    for (int i = 0; i < 10; ++i)
    {
        al_draw_line(100, 100, 200 + i * 10, 200, al_map_rgb(255, 0, 0), 2);
        al_flip_display();
        // Sleep(1000); // one second sleep, from <windows.h>
    }
    ExitAllegro();
}

struct Circle
{
    double x;
    double y;
    double dx;
    double dy;
    double r;
    void Reset()
    {
        x = SCREEN_W / 2;
        y = SCREEN_H / 2;
        r = 10.0 + rand() % 100;
        dx = 10.0 - rand() % 21;
        dy = 10.0 - rand() % 21;
    }
};

Circle circle;
void fps3()
{
    circle.x += circle.dx;
    circle.y += circle.dy;
    if ((circle.x < 1.0) ||
        (circle.x > SCREEN_W) ||
        (circle.y < 1.0) ||
        (circle.y > SCREEN_H))
    {
        circle.Reset();
    }
}

void draw3()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_filled_circle(circle.x, circle.y, circle.r, al_map_rgb(0, 255, 0));
}

int main(int argc, char **argv)
{
    srand(time(0));
    if (!InitAllegro(SCREEN_W, SCREEN_H, FPS))
    {
        DestroyAllegro();
        return 1;
    }

    // RunAllegro( 0, &draw1 );
    // RunAllegro( 0, &draw2 );
    RunAllegro(&fps3, &draw3);

    DestroyAllegro();

    // cin.get();
    return 0;
}
