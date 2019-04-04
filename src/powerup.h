#include "main.h"

#ifndef POWERUP_H
#define POWERUP_H


class Powerup {
public:
    Powerup() {}
    Powerup(float x, float y,int t, color_t color);
    glm::vec3 position;
    float rotation;
    float abspos;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_t bounding_box();
    void tick();
    double speed;
    float rad;
    float vspeed;
    int n;
    int type;
private:
    VAO *object;
    VAO *objectsp;
    VAO *objectheart;
};

#endif // POWERUP_H
