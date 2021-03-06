#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_t bounding_box();
    void tick();
    double hspeed;
    double vspeed;
    float height;
    float height2;
    float width;
private:
    VAO *object;
};

#endif // MAGNET_H
