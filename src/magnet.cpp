#include "magnet.h"
#include "main.h"

Magnet::Magnet(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 180;
    height = 0.3f;
    height2 = 0.6f;
    width = 0.3f;
    hspeed = 0;
    vspeed = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
           0.0f,0.0f,0.0f,
           width,0.0f,0.0f,
           0.0f,height,0.0f,
           width,0.0f,0.0f,
           width,height,0.0f,
           0.0f,height,0.0f, 
           width,0.0f,0.0f,
           width,height,0.0f,
           2*width,height,0.0f, 
           0.0f,0.0f,0.0f,
           0.0f,height,0.0f,
        -1*width,height,0.0f, 
           width,height,0.0f,
           2*width,height,0.0f,
           width,height + height2,0.0f,
           width,height + height2,0.0f,
           2*width,height,0.0f,
           2*width,height + height2,0.0f,
           0.0f,height,0.0f,
           -1*width,height,0.0f,
            0.0f,height + height2,0.0f,
           0.0f,height + height2,0.0f,
           -1*width,height,0.0f,
           -1*width,height + height2,0.0f,
    };  

    this->object = create3DObject(GL_TRIANGLES, 24, vertex_buffer_data, color, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Magnet::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // if(this->position.y >= 12.5 && ufl == 1) vspeed = 0;
    // if(this->position.y < 0.1 && ufl == 0) vspeed = 0;
     if(ufl == 0 && this->position.y > 0.1) vspeed-=mgf==0?0.4f:0.0f; 
    // this->position.y += vspeed;

}

bounding_box_t Magnet::bounding_box() {
    float x = this->position.x - 2*width, y = this->position.y - height - height2;
    float h = height + height2, w = 3*width  ;
    bounding_box_t bbox = { x, y, h, w, 1 };
    return bbox;
}