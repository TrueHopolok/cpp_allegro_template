// Данный пример работает на engine,
// поэтому надо изменить build скрипт
// чтобы он подключал engine.cpp

#include "engine.hpp"
#include <allegro5/allegro_primitives.h>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

struct Point {
    float x, y;
};

class IObject {
  public:
    virtual void process() = 0;
    virtual void render() = 0;
    virtual ~IObject() = default;
};

class Shape : public IObject {
  protected:
    Point origin;
    Point get_pos() {
        Point pos = origin;
        pos.x += rand() % 31 - 10;
        pos.y += rand() % 31 - 10;
        return pos;
    }

  public:
    Shape(Point pos_) : origin(pos_) {};
    virtual ~Shape() = default;
};

class Square : public Shape {
  protected:
    float size;

  public:
    Square(Point pos_, float size_) : Shape(pos_), size(size_) {};
    void process() override {}
    void render() override {
        Point pos = get_pos();
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
    void process() override {}
    void render() override {
        Point pos = get_pos();
        al_draw_filled_circle(pos.x, pos.y, size, {0, 0, 255, 0});
    }
};

class Screen : public Engine {
  private:
    vector<IObject *> objects = {};

  public:
    void add_object(IObject *obj) { objects.push_back(obj); }
    void process(double _) override {
        for (size_t i = 0; i < objects.size(); i++) {
            objects[i]->process();
        }
    }
    void render() override {
        for (size_t i = 0; i < objects.size(); i++) {
            objects[i]->render();
        }
    }

    Screen() : Engine(640, 360, 60, true) {}
};

int main() {
    Screen screen;
    screen.add_object(new Square({40, 40}, 30));
    screen.add_object(new Square({580, 60}, 50));
    screen.add_object(new Circle({60, 300}, 50));
    screen.add_object(new Circle({600, 320}, 30));
    try {
        screen.start();
    } catch (runtime_error err) {
        cout << err.what() << endl;
    } catch (exception err) {
        cout << err.what() << endl;
    }
    return 0;
}