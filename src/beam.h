#include "main.h"

#ifndef BEAM_H
#define BEAM_H


class Beam {
public:
    Beam() {}
    Beam(float x, float y,float r,int t, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_tb bounding_box();
    void tick();
    double hspeed;
    double vspeed;
    float height;
    float width;
    int type;
    int collide;
private:
    VAO *object;
    VAO *objectc;
};

#endif // BEAM_H
