#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_t bounding_box();
    bounding_box_t shbounding_box();
    void tick();
    double hspeed;
    double vspeed;
    double mspeedy;
    double mspeedx;
    float height;
    float width;
private:
    VAO *object;
    VAO *objectf;
    VAO *objectsh;
};

#endif // BALL_H
