#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    height = 1.0f;
    width = 1.0f;
    hspeed = 0;
    mspeedx = 0;
    mspeedy = 0;
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
           -width/20,0.0f,0.0f,
           -width/20,height/2,0.0f,
           -width/3,0.0f,0.0f

    };  

    static const GLfloat vertex_buffer_datafire[] = {
        (-width/3 + -width/20)/2 ,  -height/3, 0.0f,
            -width/2  , -height, 0.0f,
           -width/10 , -height, 0.0f,
    };

    static const GLfloat vertex_buffer_datashield[] = {
        width/2 + width , height + height/3, 0.0f,
        width/2 + width , 0.0f, 0.0f,
        width/2 + width + width/6 , 0.0f, 0.0f,
        width/2 + width + width/6 , 0.0f, 0.0f,
        width/2 + width , height + height/3, 0.0f,
        width/2 + width + width/6 , height+ height/3, 0.0f,
        width/2 + width + width/6 , height+ height/3, 0.0f,
        width/2 + width , height + height/3, 0.0f,
        width , height + 2*height/3 , 0.0f,
        width/2 + width , 0.0f, 0.0f,
        width/2 + width + width/6 , 0.0f, 0.0f,
        width , -height/3 , 0.0f,  
    };
    this->object = create3DObject(GL_TRIANGLES, 9, vertex_buffer_data, color, GL_FILL);
    this->objectf = create3DObject(GL_TRIANGLES, 3, vertex_buffer_datafire, COLOR_FIRE, GL_FILL);
    this->objectsh = create3DObject(GL_TRIANGLES, 12, vertex_buffer_datashield, COLOR_FIRE, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    if(sheild)  draw3DObject(this->objectsh);
    if(ufl) draw3DObject(this->objectf);

}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    if(this->position.y >= 12.5 && ufl == 1) vspeed = 0;
    if(this->position.y < 0.1 && ufl == 0) vspeed = 0;
    if(ufl == 0 && this->position.y > 0.1 && !mgf) vspeed-=(mgf2?0.05f:0.4f);
    vspeed += mspeedy;
    //hspeed += mspeedy; 
    this->position.y += vspeed;
}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float h = height, w = width;
    bounding_box_t bbox = { x, y, w, h, 1 };
    return bbox;
}

bounding_box_t Ball::shbounding_box() {
    float x = this->position.x, y = this->position.y + width/2 + width;
    float h = height + height/3, w = width/6;
    bounding_box_t bbox = { x, y, w, h, 1 };
    return bbox;
}