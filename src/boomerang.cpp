#include "boomerang.h"
#include "main.h"


Boomerang:: Boomerang(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    height = 0.5f;
    width = 0.9f;
    hspeed = -0.11f;
    time = 212.0f;
    ff = 1;
    float w23 = width*(2.0/3.0);
    vspeed = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
           0.0f,0.0f,0.0f,
           width,height,0.0f,
           0.0f,height,0.0f,
           w23,0.0f,0.0f,
           0.0f,height,0.0f,
           0.0f,0.0f,0.0f,

    };  

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Boomerang::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boomerang::tick() {
    //this->rotation += speed;
    // time --; 
    if(hspeed >= 0.2f  && ff) {
        this->rotation = 180.0f;
        ff = 0;
    }
    // time-=1;
    hspeed +=0.0015f;
    //printf("%f\n",time);
    this->position.x += hspeed;

}

bounding_box_t Boomerang::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float h = height, w = width;
    bounding_box_t bbox = { x, y, h, w, 1 };
    return bbox;
}