#include "water.h"
#include "main.h"


Water::Water(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.5;
    hspeed = 0.1;
    n = 40;
    rad = 0.1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat g_vertex_buffer_data[9*n];
    for(int i=0;i<9*n;i+=9){
      //sin (param*PI/180)
      int p = i/9;
      double k = p;
      double o = n;
      g_vertex_buffer_data[i] = 0.0f;
      g_vertex_buffer_data[i+1] = 0.0f;
      g_vertex_buffer_data[i+2] = 0.0f;

      g_vertex_buffer_data[i+5] = 0.0f;
      g_vertex_buffer_data[i+3] = (double)rad*cos(2.0*PI*(k)/o);
      g_vertex_buffer_data[i+4] = (double)rad*sin(2.0*PI*(k)/o);

      g_vertex_buffer_data[i+8] = 0.0f;
      g_vertex_buffer_data[i+6] = (double)rad*cos(2.0*PI*(k+1.0)/o);
      g_vertex_buffer_data[i+7] = (double)rad*sin(2.0*PI*(k+1.0)/o);

    }

    this->object = create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_data, color, GL_FILL);
}

void Water::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Water::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Water::tick() {
    hspeed -= 0.01;
    if(this->position.y <= 0){
      hspeed=-1*hspeed;
      hspeed-=0.06;
      speed-=0.09;
    } 
    this->position.y += hspeed;
    this->position.x += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Water::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float d = 2.0*rad;
    bounding_box_t bbox = { (float)( x - rad),(float)(y - rad), d, d, 2 };
    return bbox;
}