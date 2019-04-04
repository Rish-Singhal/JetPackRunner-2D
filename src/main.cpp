#include "main.h"
#include "timer.h"
#include "ball.h"
#include "coin.h"
#include "platform.h"
#include "boomerang.h"
#include "water.h"
#include "beam.h"
#include "magnet.h"
#include "powerup.h"
#include "ring.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

/*
   Coin : 2
   Ball : 1

*/

float randf(float lo, float hi) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = hi - lo;
    float r = random * diff;
    return lo + r;
}

Ball ball;
bool sheild = 0;
float start_pos = 13;
Platform fl,cl;
vector <Coin> coin;
vector <Boomerang> en3;
vector <Water> s1;
vector <Beam> en1;
vector <Beam> en2;
vector <Magnet> mg;
vector <Powerup> pp;
vector <Ring> ring;

color_t backk[] = {COLOR_BACKGROUND,COLOR_BACKGROUND2,COLOR_BACKGROUND3};

bool ufl = 0, mgf =0, mgf2 =0;
    float t = 20, t2 = 50, t3 = 50, t7 = 100;
    float mult = 1;
float screen_zoom = 0.5f, screen_center_x = 0, screen_center_y = 7;
float camera_rotation_angle = 100, col = 0;
float abs_distance = 0.0f;
bool rrr = 0;

Timer t60(1.0 / 60);

int game_lives = 3;
int game_score = 0;
int game_level = 1;
float dis1 = 0.0f;
float dis2 = 0.0f;
float dis3 = 50.0f;
float dis4 = 0.0f;
float dis5 = 300.0f;
float dis6 = 400.0f;
int lvlcount = 150;

bool pressed = 0;
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    for(auto &c : coin )  c.draw(VP);
    for(auto &c : en3 )  c.draw(VP);  
    for(auto &c : en1 )  c.draw(VP); 
    for(auto &c : en2 )  c.draw(VP);  
    for(auto &c : s1 )  c.draw(VP); 
    for(auto &c : mg )  c.draw(VP);
    for(auto &c : pp )  c.draw(VP);
    for(auto &c : ring )  c.draw(VP);      
    ball.draw(VP);
    fl.draw(VP);
    cl.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    int shoot = glfwGetKey(window, GLFW_KEY_S);
    if (left && ufl ==0 && rrr == 0) {
      
       ball.position.x = max(ball.position.x - 0.1,(double)game_left());
       pressed = 1;       
    }
    if( left == GLFW_RELEASE) pressed = 0;
    if(right && ufl ==0 && rrr ==0) {
       // screen_zoom+=0.1f;
       // cout<<screen_zoom<<endl;
        ball.position.x = min(ball.position.x + 0.1,(double)game_right());
        pressed = 2;
    }
    if( right == GLFW_RELEASE) pressed = 0;
    if (up == GLFW_PRESS && ufl == 0 && mgf ==0 && rrr == 0) {
        ufl = 1;
      //  ball.position.y+=1;
        ball.vspeed = 0.3f;
    }
    if (up == GLFW_RELEASE ){ 
        ball.vspeed = 0;
        ufl = false;
    }
    bool wch = 1; 
    if(shoot == GLFW_PRESS && wch == 1){
          Water x = Water(ball.position.x + ball.width,ball.position.y + ball.height,COLOR_WATER);
          s1.push_back(x);
          if(s1.size()>100) s1.erase(s1.begin());
          wch = 0;
    }
    if(shoot == GLFW_RELEASE) wch = 1;
}

void tick_elements() {
    if(lvlcount < game_score){
        game_level++;
        game_score = 0;
        lvlcount += 100;
    }
    // for(auto &c : ring){
    //     if(detect_collision(c.bounding_box(),ball.bounding_box()) && rrr == 0){
    //         rrr = 1;
    //         ball.rotation = 90;
    //     }
    // }
    if(ball.position.x!= game_left()+2 && ball.position.y==0 && pressed == 0){
        ball.position.x+=(game_left() + 2 > ball.position.x?0.05:-0.05);
    } 
    if(t <= 0){
        if(mg.size()){
        mgf = 0;
        mgf2 = 0;
        mg.erase(mg.begin());}

    }
    if(t3 <= 0){
        while(en2.size()){
                    en2.erase(en2.begin());
                }
    }
    if(t2 <= 0){
       // if(t2==0) printf("powerup: ended");
        mult = 1;
    }
    if(t7 <= 0){
        sheild = 0;
    }
    //ball.position.x = max(ball.position.x , 0);
    if(ball.position.y < 0.2f) ball.position.y = 0.0f; 
    ball.position.y = max(ball.position.y , 0.0f);
    for(auto &c:coin) c.position.x -= 0.15;
    for(auto &c:en3) c.position.x -= 0.15;
    for(auto &c:s1) c.position.x -= 0.15;
   for(auto &c:en1) if(c.type == 1) c.position.x -= 0.15;
   for(auto &c:pp) c.position.x -= 0.15; 
    for(auto &c:ring) c.position.x -=0.05;
    t -=0.2 , t2-=0.2, t3-=0.2, t7-=0.2;
   //for(auto &c:mg) c.position.x -= 0.2;    
    abs_distance += 0.2;
    for(auto &c:mg){
        float mx = c.position.x - c.width - c.width;
        float my = c.position.y - c.height;
        float px = ball.position.x;
        float py = ball.position.y;
        float v1 = mx - px , v2 = my - py;
        float d = sqrt(v1*v1 + v2*v2);
        float v3 = v1/d;
        float v4 = v2/d;
        int t =0;
        if(d > 10){ mgf2 =0 ; continue;}
        if(detect_collision(c.bounding_box(),ball.bounding_box())) t++;
        if(detect_collision(c.bounding_box(),ball.bounding_box())){
            //if(c == mg.begin())
           // cout<<"yesss"<<endl;
            //cout<<t<<endl;
            ball.mspeedy =0;
            ball.hspeed = 0;
            ball.vspeed = 0;
            mgf =1;
            ball.position.x += 0.2*v3;
            //ball.position.y = my - c.height2;
           // t++;
        }
       if(!mgf){
        ball.position.x += 0.3*v3/d;
        ball.position.y += 0.3*v4/d;
        mgf2 =1;
        }

     //   else mgf = 0;
    }
    for(auto c = s1.begin(); c < s1.end() ; ){
        if(c->position.y < 0 && c->hspeed == 0){
             c = s1.erase(c);
        }
        else c++;
    }

  for(auto c = en3.begin(); c < en3.end() ; ){
        if(c->time > 600){
             c = en3.erase(c);
        }
        else c++;
    }

    if(randf(0.0f,1.0f) <= 0.03f){
            int type;
            color_t c;
            if(randf(0.0f,1.0f)>=0.3f){
                type = 1;
                c = COLOR_YELLOW;
            }
            else {
                type = 2;
                c = COLOR_RED;
            }
            Coin x  = Coin(start_pos, randf(1.0f,13.0f), type, c);
            coin.push_back(x);
        }

    if( abs_distance >= dis1 ){
        en3.clear();
        Boomerang boom = Boomerang(start_pos, randf(1.0f,13.0f),COLOR_MAG);
        en3.push_back(boom);
        dis1 += max(120.0f - game_level*(20.0f),60.0f);
    }
    if( abs_distance >= dis2 && en2.size()==0 ){
        if(en1.size()>=10) en1.erase(en1.begin());
        Beam bm = Beam(start_pos, randf(1.0f,13.0f),randf(0.0f,360.0f),1,COLOR_FIRE);
        Beam bm2 = Beam(20, randf(1.0f,13.0f),randf(0.0f,360.0f),1,COLOR_FIRE);
        en1.push_back(bm);
        en1.push_back(bm2);
        dis2 += 50.0f;
    }

    if( abs_distance >= dis6 ){
        Beam bm = Beam(-6, 2,-90,21,COLOR_FIRE);
        Beam bm2 = Beam(-6, 12,-90,22,COLOR_FIRE);
        en2.push_back(bm);
        en2.push_back(bm2);
        t3  = 90.0f;
        dis6 += max(400.0f - game_level*(50.0f),150.0f);
    }

    if( abs_distance >= dis4 ){
            int type;
            color_t c;
            float ppx = randf(0.0f,1.0f);
            if(ppx<=0.3f){
                type = 1;
                c = COLOR_YELLOW;
            }
            else if(ppx <=0.7f) {
                type = 2;
                c = COLOR_RED;
            }
            else {
                type = 3;
                c = COLOR_YELLOW;
            }
            Powerup x  = Powerup(start_pos,(type==3?10.0f:randf(4.0f,10.0f)), type, c);
            pp.push_back(x);
            dis4+=randf(200.0f,240.0f);
    }

    if( abs_distance >= dis3 ){ 
           Magnet zz = Magnet(randf(0,7),randf(7,14),COLOR_DBLACK);
           mg.push_back(zz);
           t = 20;
           dis3 += max(300.0f - game_level*(20.0f),150.0f);
    }

    ball.tick();
    for(auto &c:coin) c.tick();  
    for(auto &c:en3) c.tick();
    for(auto &c:s1) c.tick(); 
    for(auto &c:en1) c.tick();
    for(auto &c:en2) c.tick();
    for(auto &c:pp) c.tick(); 
    for(auto &c:ring) c.tick();    
    for(auto c = coin.begin(); c < coin.end() ; ){
        if(detect_collision(c->bounding_box(),ball.bounding_box())){
            if(c->type == 1) game_score +=mult*1;
            else game_score += mult*4;
            c = coin.erase(c);
            printf("new score : %d\n",game_score);
        }
        else c++;
    }

    for(auto c = pp.begin(); c < pp.end() ; ){
        if(detect_collision(c->bounding_box(),ball.bounding_box())){
            if(c->type == 1){ 
                mult += 3;
                t2 = 50;
                printf("powerup : multiplier");
            }
            else if (c->type == 2){
                game_lives ++;
                printf("powerup : lives++");
            }
            else if(c->type == 3){
                sheild = 1;
                t7 = 80;
                printf("special powerup : sheild");
            }
            //else game_score += 4;
            c = pp.erase(c);
           
        }
        else c++;
    }
    for(auto c = en1.begin(); c < en1.end() ; ){
        if(detect_collision2(c->bounding_box(),ball.bounding_box()) && c->collide ==0){
                c->collide = 1;
                if(!sheild)game_lives -=1;
                c = en1.erase(c);
                if(game_lives == 0) {
                    printf("GAME _OVER\n");
                    exit(0);
                }
        }
        else c++;
    } 
    for(auto c = en2.begin(); c < en2.end() ; ){
        if(detect_collision2(c->bounding_box(),ball.bounding_box()) && c->collide ==0){
                c->collide = 1;
                if(!sheild)game_lives -=1;
                while(en2.size()){
                    en2.erase(en2.begin());
                }
                if(game_lives == 0) {
                    printf("GAME _OVER\n");
                    exit(0);
                }
        }
        else c++;
    }   
    for(auto c = en1.begin(); c < en1.end() ; ){

        for(auto c2 = s1.begin(); c2 < s1.end() ; )
         {
            if(detect_collision2(c->bounding_box(),c2->bounding_box()) && c->collide == 0){
                c->collide = 1;
                c2 = s1.erase(c2);
                c = en1.erase(c);
              }
            else c2++;
         }
        c++;
    }   
    for(auto c = en3.begin(); c < en3.end() ; c++){
        if(detect_collision(c->bounding_box(),ball.bounding_box())){
            if(!sheild)game_score -=10;
            //else game_score += 4;
            game_score = max(game_score,0);
            c = en3.erase(c);
            printf("new score : %d\n",game_score);
        }
    }

char mscore[256];
    sprintf(mscore, "JetPack JOYRIDE 1.0 Level: %d | Lives :%d | Score: %d | dist: %f",game_level,game_lives,game_score,abs_distance);
    glfwSetWindowTitle(window, mscore);
    //camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball    = Ball(-5, 0, COLOR_DBLACK);
    fl   = Platform(-10.0f,-2.0f,COLOR_BLACK);
    cl  = Platform(-10.0f,13.7f,COLOR_BLACK);
   // Ring xx = Ring(10,0,COLOR_BLACK);
   // ring.push_back(xx);
  //Powerup x  = Powerup(13,10,3,COLOR_YELLOW);
    //pp.push_back(x);
   // Magnet x = Magnet(0,14,COLOR_DBLACK);
  //  Magnet y = Magnet(0.9,7,COLOR_DBLACK);
    //mg.push_back(x);
   // mg.push_back(y);
    //Boomerang boom = Boomerang(start_pos.0f,7.0f,COLOR_MAG);

    //en3.push_back(boom);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (backk[min(game_level-1,2)].r / 256.0, backk[min(game_level-1,2)].g / 256.0, backk[min(game_level-1,2)].b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);
    glClearColor(0.0f, 0.5f, 0.5f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT); 

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

bool detect_collision2(bounding_box_tb a, bounding_box_t b) {
    float xx = b.x + b.width/2 , yy = b.y + b.height/2;
    float rr = b.width/2;
    float x1 = a.x, x2 = a.x - (a.height*sin(a.ra*M_PI/180.0));
    float y1 = a.y, y2 = a.y + (a.height*cos(a.ra*M_PI/180.0));
    float v1 = x2 - x1,v2 = y2 - y1; float d = sqrt(v1*v1 + v2*v2);
    float dot = (xx - a.x)*(v1/d) + (yy -a.y)*(v2/d);
    float d2 = sqrt((xx - a.x)*(xx - a.x) +(yy -a.y)*(yy -a.y));
 //   cout<<d2<<endl;
    if(dot >= a.height) {
        //cout<<" d >= a.height"<<endl;

        return 0;
    }
    if(dot < 0){
       // cout<<"dot == 0"<<endl;
     return 0;
 }
    else{
        float op = sqrt(d2*d2 - dot*dot);
       // cout<<" other "<<op<<endl;
        return op <= rr + 0.4;
    }
   // return 0;
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

float game_left(){
    return screen_center_x - 4 / screen_zoom;
}


float game_right(){
    return screen_center_x + 4 / screen_zoom;
}