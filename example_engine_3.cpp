#include "engine.hpp"
#include <allegro5/allegro_primitives.h>
#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

struct Point {
    float x, y;
};

class IObject {
  public:
    virtual void fps_update() = 0;
    virtual void draw_update() = 0;
    virtual ~IObject() = default;
};

class Shape : public IObject {
  protected:
    Point pos;

  public:
    Shape(Point pos_) : pos(pos_) {};
    virtual ~Shape() = default;
};

class Square : public Shape {
  protected:
    float size;

  public:
    Square(Point pos_, float size_) : Shape(pos_), size(size_) {};
    void fps_update() override {}
    void draw_update() override {
        al_draw_filled_rectangle(pos.x - size / 2, pos.y - size / 2,
                                 pos.x + size / 2, pos.y + size / 2,
                                 {255, 0, 0, 0});
    }
};

class Circle : public Shape {
  protected:
    float size;

  public:
    Circle(Point pos_, float size_) : Shape(pos_), size(size_) {};
    void fps_update() override {}
    void draw_update() override {
        al_draw_filled_circle(pos.x, pos.y, size, {0, 0, 255, 0});
    }
};

class Screen {
  private:
    inline static Screen *instance = nullptr;
    vector<IObject *> objects = {};
    Screen() {};

  public:
    static Screen *get_instance() {
        if (instance == nullptr) {
            instance = new Screen();
        }
        return instance;
    }
    void add_object(IObject *obj) { objects.push_back(obj); }
    void fps_update() {
        for (size_t i = 0; i < objects.size(); i++) {
            objects[i]->fps_update();
        }
    }
    void draw_update() {
        for (size_t i = 0; i < objects.size(); i++) {
            objects[i]->draw_update();
        }
    }
};

void fps_update() { Screen::get_instance()->fps_update(); }

void draw_update() { Screen::get_instance()->draw_update(); }

int main() {
    Screen *screen = Screen::get_instance();
    screen->add_object(new Square({40, 40}, 30));
    screen->add_object(new Square({580, 60}, 50));
    screen->add_object(new Circle({60, 300}, 50));
    screen->add_object(new Circle({600, 320}, 30));
    try {
        Engine::start(fps_update, draw_update);
    } catch (char const *error) {
        cout << error << endl;
    }
    return 0;
}