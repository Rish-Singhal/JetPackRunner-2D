#include "powerup.h"
#include "main.h"


Powerup::Powerup(float x, float y, int t, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    abspos = y;
    vspeed = (type == 3?0.3:0.2);
    speed = 0.3;
    type = t ;
    n = 40;
    rad = (t==1?0.4:0.5);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat g_vertex_buffer_dataheart[] = {
           -rad,0.0f,0.0f,
           rad,0.0f,0.0f,
           0.0f,-rad,0.0f,
           -rad,0.0f,0.0f,
           0.0f,0.0f,0.0f,
           -rad/2.0f,2*rad/3.0f,0.0f,
          rad,0.0f,0.0f,
           0.0f,0.0f,0.0f,
           rad/2.0f,2*rad/3.0f,0.0f,

    };  

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
    GLfloat g_vertex_buffer_datasp[9*n];
    for(int i=0;i<9*n;i+=9){
      //sin (param*PI/180)
      int p = i/9;
      double k = p;
      double o = n;
      g_vertex_buffer_datasp[i] = 0.0f;
      g_vertex_buffer_datasp[i+1] = 0.0f;
      g_vertex_buffer_datasp[i+2] = 0.0f;

      g_vertex_buffer_datasp[i+5] = 0.0f;
      g_vertex_buffer_datasp[i+3] = (double)rad/2*cos(2.0*PI*(k)/o);
      g_vertex_buffer_datasp[i+4] = (double)rad/2*sin(2.0*PI*(k)/o);

      g_vertex_buffer_datasp[i+8] = 0.0f;
      g_vertex_buffer_datasp[i+6] = (double)rad/2*cos(2.0*PI*(k+1.0)/o);
      g_vertex_buffer_datasp[i+7] = (double)rad/2*sin(2.0*PI*(k+1.0)/o);

    }
    this->object = create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_data, color, GL_FILL);
    this->objectsp = create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_datasp, COLOR_FIRE, GL_FILL);
    this->objectheart = create3DObject(GL_TRIANGLES, 9, g_vertex_buffer_dataheart, COLOR_HEART, GL_FILL);
}

void Powerup::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    if(type == 2){
      draw3DObject(this->objectheart);
    }
    else{
    draw3DObject(this->object);
    if(type == 3) draw3DObject(this->objectsp);
  }
}

void Powerup::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Powerup::tick() {
    // this->position.x -= speed;
  if(type!=3){
      float d = abspos - this->position.y;
     //float d = -1;
     vspeed+=(d>0?0.01:-0.01);
     this->position.y += vspeed;
   }
   else{
    if(this->position.y-rad<= 0){
      vspeed=-1*vspeed;
      vspeed-=0.06;
    } 

      vspeed -= 0.02;
      this->position.y += vspeed;
   }

}

bounding_box_t Powerup::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float d = 2.0*rad;
    bounding_box_t bbox = { (float)( x - rad),(float)(y - rad), d, d, 2 };
    return bbox;
}