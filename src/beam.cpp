#include "beam.h"
#include "main.h"

Beam::Beam(float x, float y, float r, int t,  color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = r;
    height = (t==1?4.0f:12.0f);
    width = 0.2f;
    hspeed = 0;
    vspeed = 0.01;
    type = t;
    int n = 6;
    double rad = 0.3f;
    collide = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[6*3 + 18*n] = {
           0.0f,0.0f,0.0f,
           0.0f,0.0f,width,
           0.0f,height,0.0f,
           0.0f,0.0f,width,
           0.0f,height,width,
           0.0f,height,0.0f,
    }; 

    GLfloat vertex_buffer_data2[9*n];

    for(int i=6*3 + 1;i< (6*3+9*n);i+=9){
      int p = i/9;
      double k = p;
      double o = n;
      vertex_buffer_data[i] = 0.0f;
      vertex_buffer_data[i+1] =(double)0.0f;
      vertex_buffer_data[i+2] = 0.0f;   

      vertex_buffer_data[i+5] = 0.0f;
      vertex_buffer_data[i+3] = (double) (double)rad*cos(2.0*PI*(k)/o);
      vertex_buffer_data[i+4] = (double)width/2 +rad*sin(2.0*PI*(k)/o);

      vertex_buffer_data[i+8] = 0.0f;
      vertex_buffer_data[i+6] = (double)(double)rad*cos(2.0*PI*(k+1.0)/o);
      vertex_buffer_data[i+7] = (double)width/2 +rad*sin(2.0*PI*(k+1.0)/o);

    }
 

    for(int i=6*3 + 9*n + 1;i< (6*3+18*n);i+=9){
      int p = i/9;
      double k = p;
      double o = n;
      vertex_buffer_data[i] = height;
      vertex_buffer_data[i+1] =(double)width/2;
      vertex_buffer_data[i+2] = 0.0f;   

      vertex_buffer_data[i+5] = 0.0f;
      vertex_buffer_data[i+3] = (double) height +(double)rad*cos(2.0*PI*(k)/o);
      vertex_buffer_data[i+4] = width/2 + rad*sin(2.0*PI*(k)/o);

      vertex_buffer_data[i+8] = 0.0f;
      vertex_buffer_data[i+6] = (double)height +(double)rad*cos(2.0*PI*(k+1.0)/o);
      vertex_buffer_data[i+7] = width/2+ rad*sin(2.0*PI*(k+1.0)/o);

    }

    for(int i=0;i< (9*n);i+=9){
      int p = i/9;
      double k = p;
      double o = n;
      vertex_buffer_data2[i] = 0.0f;
      vertex_buffer_data2[i+1] =(double)0.0f;
      vertex_buffer_data2[i+2] = 0.0f;   

      vertex_buffer_data2[i+5] = 0.0f;
      vertex_buffer_data2[i+3] = (double) (double)rad*cos(2.0*PI*(k)/o);
      vertex_buffer_data2[i+4] = (double)width/2 +rad*sin(2.0*PI*(k)/o);

      vertex_buffer_data2[i+8] = 0.0f;
      vertex_buffer_data2[i+6] = (double)(double)rad*cos(2.0*PI*(k+1.0)/o);
      vertex_buffer_data2[i+7] = (double)width/2 +rad*sin(2.0*PI*(k+1.0)/o);

    }
    this->object = create3DObject(GL_TRIANGLES, 6 + 6*n, vertex_buffer_data, color, GL_FILL);
    this->objectc = create3DObject(GL_TRIANGLES, 3*n , vertex_buffer_data2, color, GL_FILL);
}

void Beam::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (90 * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate2    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0,0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate2 * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(!collide)draw3DObject(this->object);
    else draw3DObject(this->objectc); 
}

void Beam::set_position(float x, float y) {
   // this->position = glm::vec3(x, y, 0);
}

void Beam::tick() {
    if(type == 1 )this->rotation += 2;
    if(type == 21){
        if(this->position.y < 0) vspeed =-vspeed;
        if(this->position.y > 3) vspeed =-vspeed;
         this->position.y +=vspeed;
    }
    if(type == 22){
          if(this->position.y > 14) vspeed =-vspeed;
           if(this->position.y < 10) vspeed =-vspeed;
         this->position.y +=vspeed; 
    }
    // if(type == 2){

    //  this->position.y += 0.01;
    // }
   // printf("%f\n",this->rotation);
    // this->position.x -= speed;
    // if(this->position.y >= 12.5 && ufl == 1) vspeed = 0;
    // if(this->position.y < 0.1 && ufl == 0) vspeed = 0;
    // if(ufl == 0 && this->position.y > 0.1) vspeed-=0.4f; 
    // this->position.y += vspeed;

}

bounding_box_tb Beam::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float h = height, w = width;
    bounding_box_tb bbox = { x, y, w, h, 1 , this->rotation};
    return bbox;
}