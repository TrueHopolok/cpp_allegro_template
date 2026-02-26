// Данный пример работает на engine,
// поэтому надо изменить build скрипт
// чтобы он подключал engine.cpp

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
    virtual void physics_process() = 0;
    virtual void render_process() = 0;
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
    void physics_process() override {}
    void render_process() override {
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
    void physics_process() override {}
    void render_process() override {
        al_draw_filled_circle(pos.x, pos.y, size, {0, 0, 255, 0});
    }
};

class Screen : public Engine {
  private:
    vector<IObject *> objects = {};

  public:
    void add_object(IObject *obj) { objects.push_back(obj); }
    void physics_process() override {
        for (size_t i = 0; i < objects.size(); i++) {
            objects[i]->physics_process();
        }
    }
    void render_process() override {
        for (size_t i = 0; i < objects.size(); i++) {
            objects[i]->render_process();
        }
    }
};

int main() {
    Screen screen;
    screen.add_object(new Square({40, 40}, 30));
    screen.add_object(new Square({580, 60}, 50));
    screen.add_object(new Circle({60, 300}, 50));
    screen.add_object(new Circle({600, 320}, 30));
    try {
        screen.start();
    } catch (char const *error) {
        cout << error << endl;
    }
    return 0;
}