#include "main.h"
#include "timer.h"
#include "plane.h"
#include "ground.h"
#include "dashboard.h"
#include "ring.h"
#include "volcano.h"
#include "canon.h"
#include "missile.h"
#include "pmissile.h"
#include "bomb.h"
#include "compass.h"
#include "fuel.h"
#include "parachute.h"
#include "arrow.h"
#include "checkpoint.h"
#include "display.h"

using namespace std;

GLMatrices Matrices;
GLMatrices ortho_projection;
GLuint     programID;
GLFWwindow *window;

int t = 0;
int score = 0;
int bom = 0;
int rolls = 0;
/**************************
* Customizable functions *
**************************/
int one = 0,two = 0,three = 0,four = 0;
Plane plane1;
Ground ground;
Dashboard dashboard_fuel;
Dashboard dashboard_altitude;
Dashboard dashboard_speed;
Compass compass;
std::vector<Ring> ring;
std::vector<Volcano> volcano;
std::vector<PMissile> pmissile;
std::vector<Bomb> bomb;
std::vector<Canon> canon;
std::vector<Missile> missile;
std::vector<Fuel> fuel;
std::vector<Parachute> parachute;
std::vector<Arrow> arrow;
std::vector<Checkpoint> checkpoint;
Display display1;
Display display2;
Display display3;
Display display4;


float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

float radius = 5.0f;
float camX = 0, camZ = radius;

Timer t60(1.0 / 60);

glm::vec3 eye2 (0,0,0);
glm::vec3 target2 (0,0,0);
glm::vec3 up2 (0,0,0);

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
    printf("%lf %lf\n",xpos, ypos);
    printf("%f %f %f\n", eye2.x, eye2.y, eye2.z);
    if(xpos > 300.0f)
        eye2.x += 0.05;
    else
        eye2.x -= 0.05;
}


/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    //Follow-cam view- done
    glm::vec3 eye (plane1.position[0] + 4*(plane1.coord[1].x) + 3*(plane1.coord[2].x), plane1.position[1] + 4*(plane1.coord[1].y) + 3*(plane1.coord[2].y) , plane1.position[2] + 4*(plane1.coord[1].z) + 3*(plane1.coord[2].z));
    glm::vec3 target (plane1.position[0], plane1.position[1], plane1.position[2]);
    glm::vec3 up (plane1.coord[1].x, plane1.coord[1].y, plane1.coord[1].z);

    if(!four)
    {
        eye2 = eye;
        target2 = target;
        up2 = up;
    }
    //Plane view
    if (one) {
        printf("Plane view please\n");
        eye.x = plane1.position[0] - 2*(plane1.coord[2].x);
        eye.y = plane1.position[1] - 2*(plane1.coord[2].y);
        eye.z = plane1.position[2] - 2*(plane1.coord[2].z);

        target.x = plane1.position[0] - 10*(plane1.coord[2].x);
        target.y = plane1.position[1] - 10*(plane1.coord[2].y);
        target.z = plane1.position[2] - 10*(plane1.coord[2].z);

    }
    //Top view- done
    else if (two) {
        printf("Top view please\n");
        eye.x = plane1.position[0] + 20*(plane1.coord[1].x);
        eye.y = plane1.position[1] + 20*(plane1.coord[1].y);
        eye.z = plane1.position[2] + 20*(plane1.coord[1].z);

        up.x = 0;
        up.y = 0;
        up.z = -1;
    }
    //Tower view- done
    else if (three) {
        eye.x = -5;
        eye.y = 5;
        eye.z = plane1.position[2];
    }

    //Helicopter-cam view
    else if (four) {
        printf("%f %f %f\n", eye2.x, eye2.y, eye2.z);
        // glfwSetCursorPosCallback(window, cursor_pos_callback);
        double xpos, ypos;
        glfwGetCursorPos (window, &xpos, &ypos);
        if(xpos > 300.0f)
            eye2.x += 0.05;
        else
            eye2.x -= 0.05;
    }
    // Compute Camera matrix (view)
    if(!four)
    {
        Matrices.view = glm::lookAt( eye, target, up );
    }// Rotating Camera for 3D
    if(four)
        Matrices.view = glm::lookAt(eye2, target2, up2);

    ortho_projection.view = glm::lookAt( eye, target, up );

    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 ortho_VP = ortho_projection.projection * ortho_projection.view;


    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ground.draw(VP);

    plane1.draw(VP);
    dashboard_altitude.draw(ortho_VP);
    dashboard_fuel.draw(ortho_VP);
    dashboard_speed.draw(ortho_VP);
    compass.draw(ortho_VP);
    display1.draw(ortho_VP);
    display2.draw(ortho_VP);
    display3.draw(ortho_VP);
    display4.draw(ortho_VP);

    for (int i = 0; i < ring.size(); ++i)
    {
        ring[i].draw(VP);
    }
    for (int i = 0; i < volcano.size(); ++i)
    {
        volcano[i].draw(VP);
    }
    for (int i = 0; i < pmissile.size(); ++i)
    {
        pmissile[i].draw(VP);
    }
    for (int i = 0; i < bomb.size(); ++i)
    {
        bomb[i].draw(VP);
    }
    for (int i = 0; i < canon.size(); ++i)
    {
        canon[i].draw(VP);
    }
    for (int i = 0; i < missile.size(); ++i)
    {
        missile[i].draw(VP);
    }
    for (int i = 0; i < fuel.size(); ++i)
    {
        fuel[i].draw(VP);
    }
    for (int i = 0; i < parachute.size(); ++i)
    {
        parachute[i].draw(VP);
    }
    for (int i = 0; i < checkpoint.size(); ++i)
    {
        checkpoint[i].draw(VP);
    }
    // arrow.draw(VP);
    // for (int i = 0; i < arrow.size(); ++i)
    // {
    //     arrow[i].draw(VP);
    // }
    arrow[t].draw(VP);
    // glm::vec3 d = target - eye;
    // glm::vec3 u = glm::normalize(d);
    if(one == 0 && two == 0 && three == 0 && four == 0)
    {
        dashboard_altitude.position.x = plane1.position.x + 2*(plane1.coord[2].x) - 2.5*(plane1.coord[0].x) - 2.5*(plane1.coord[1].x);
        dashboard_altitude.position.y = plane1.position.y + 2*(plane1.coord[2].y) - 2.5*(plane1.coord[0].y) - 2.5*(plane1.coord[1].y);
        dashboard_altitude.position.z = plane1.position.z + 2*(plane1.coord[2].z) - 2.5*(plane1.coord[0].z) - 2.5*(plane1.coord[1].z);

        dashboard_fuel.position.x = plane1.position.x + 2*(plane1.coord[2].x) - 1.4*(plane1.coord[0].x) - 2.5*(plane1.coord[1].x);
        dashboard_fuel.position.y = plane1.position.y + 2*(plane1.coord[2].y) - 1.4*(plane1.coord[0].y) - 2.5*(plane1.coord[1].y);
        dashboard_fuel.position.z = plane1.position.z + 2*(plane1.coord[2].z) - 1.4*(plane1.coord[0].z) - 2.5*(plane1.coord[1].z);

        dashboard_speed.position.x = plane1.position.x + 2*(plane1.coord[2].x) - 0.3*(plane1.coord[0].x) - 2.5*(plane1.coord[1].x);
        dashboard_speed.position.y = plane1.position.y + 2*(plane1.coord[2].y) - 0.3*(plane1.coord[0].y) - 2.5*(plane1.coord[1].y);
        dashboard_speed.position.z = plane1.position.z + 2*(plane1.coord[2].z) - 0.3*(plane1.coord[0].z) - 2.5*(plane1.coord[1].z);

        compass.position.x = plane1.position.x + 2*(plane1.coord[2].x) + 2.5*(plane1.coord[0].x) - 2.5*(plane1.coord[1].x);
        compass.position.y = plane1.position.y + 2*(plane1.coord[2].y) + 2.5*(plane1.coord[0].y) - 2.5*(plane1.coord[1].y);
        compass.position.z = plane1.position.z + 2*(plane1.coord[2].z) + 2.5*(plane1.coord[0].z) - 2.5*(plane1.coord[1].z);

        display1.position.x = plane1.position.x + 2*(plane1.coord[2].x) + 3.5*(plane1.coord[0].x) + 2.5*(plane1.coord[1].x);
        display1.position.y = plane1.position.y + 2*(plane1.coord[2].y) + 3.5*(plane1.coord[0].y) + 2.5*(plane1.coord[1].y);
        display1.position.z = plane1.position.z + 2*(plane1.coord[2].z) + 3.5*(plane1.coord[0].z) + 2.5*(plane1.coord[1].z);

        display2.position.x = plane1.position.x + 2*(plane1.coord[2].x) + 3.2*(plane1.coord[0].x) + 2.5*(plane1.coord[1].x);
        display2.position.y = plane1.position.y + 2*(plane1.coord[2].y) + 3.2*(plane1.coord[0].y) + 2.5*(plane1.coord[1].y);
        display2.position.z = plane1.position.z + 2*(plane1.coord[2].z) + 3.2*(plane1.coord[0].z) + 2.5*(plane1.coord[1].z);

        display3.position.x = plane1.position.x + 2*(plane1.coord[2].x) + 2.9*(plane1.coord[0].x) + 2.5*(plane1.coord[1].x);
        display3.position.y = plane1.position.y + 2*(plane1.coord[2].y) + 2.9*(plane1.coord[0].y) + 2.5*(plane1.coord[1].y);
        display3.position.z = plane1.position.z + 2*(plane1.coord[2].z) + 2.9*(plane1.coord[0].z) + 2.5*(plane1.coord[1].z);

        display4.position.x = plane1.position.x + 2*(plane1.coord[2].x) + 2.6*(plane1.coord[0].x) + 2.5*(plane1.coord[1].x);
        display4.position.y = plane1.position.y + 2*(plane1.coord[2].y) + 2.6*(plane1.coord[0].y) + 2.5*(plane1.coord[1].y);
        display4.position.z = plane1.position.z + 2*(plane1.coord[2].z) + 2.6*(plane1.coord[0].z) + 2.5*(plane1.coord[1].z);
    }
        
    
}

void tick_input(GLFWwindow *window) {

    int forward = glfwGetKey(window, GLFW_KEY_W);
    int left = glfwGetKey(window, GLFW_KEY_Q);
    int right = glfwGetKey(window, GLFW_KEY_E);
    int roll_left = glfwGetKey(window, GLFW_KEY_A);
    int roll_right = glfwGetKey(window, GLFW_KEY_D);
    int pi_up = glfwGetKey(window, GLFW_KEY_Z);
    int pi_down = glfwGetKey(window, GLFW_KEY_X);
    int pmissile_shoot = glfwGetKey(window, GLFW_KEY_M);

    int state1 = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    int state2 = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

    int bomb_shoot = glfwGetKey(window, GLFW_KEY_B);
    int barrel_roll = glfwGetKey(window, GLFW_KEY_L);

    if(forward)
    {
        plane1.move_forward();
        dashboard_altitude.move_forward();
        dashboard_speed.move_forward();
        dashboard_fuel.move_forward();
        compass.move_forward();
        display1.move_forward();
        display2.move_forward();
        display3.move_forward();
        display4.move_forward();
    }
    if(left)
    {
        plane1.tilt_left();
        dashboard_speed.tilt_left();
        dashboard_altitude.tilt_left();
        dashboard_fuel.tilt_left();
        compass.tilt_left();
        display1.tilt_left();
        display2.tilt_left();
        display3.tilt_left();
        display4.tilt_left();

    }
    if(right)
    {
        plane1.tilt_right();
        dashboard_fuel.tilt_right();
        dashboard_altitude.tilt_right();
        dashboard_speed.tilt_right();
        compass.tilt_right();
        display1.tilt_right();
        display2.tilt_right();
        display3.tilt_right();
        display4.tilt_right();
    }
    if(roll_left)
    {
        plane1.roll_clk();
        dashboard_fuel.roll_clk();
        dashboard_altitude.roll_clk();
        dashboard_speed.roll_clk();
        compass.roll_clk();
        display1.roll_clk();
        display2.roll_clk();
        display3.roll_clk();
        display4.roll_clk();
    }
    if(roll_right)
    {
        plane1.roll_aclk();
        dashboard_fuel.roll_aclk();
        dashboard_altitude.roll_aclk();
        dashboard_speed.roll_aclk();
        compass.roll_aclk();
        display1.roll_aclk();
        display2.roll_aclk();
        display3.roll_aclk();
        display4.roll_aclk();
    }
    if(pi_up)
    {
        plane1.pitch_up();
        dashboard_speed.pitch_up();
        dashboard_altitude.pitch_up();
        dashboard_fuel.pitch_up();
        compass.pitch_up();
        display1.pitch_up();
        display2.pitch_up();
        display3.pitch_up();
        display4.pitch_up();
    }
    if(pi_down)
    {
        plane1.pitch_down();
        dashboard_fuel.pitch_down();
        dashboard_altitude.pitch_down();
        dashboard_speed.pitch_down();
        compass.pitch_up();
        display1.pitch_up();
        display2.pitch_up();
        display3.pitch_up();
        display4.pitch_up();
    }
    if(pmissile_shoot && bom%13 == 0)
    {
        pmissile.push_back(PMissile(plane1.position[0], plane1.position[1], plane1.position[2], COLOR_GREEN));
    }
    //
    if(state1 && bom%13 == 0)
    {
        pmissile.push_back(PMissile(plane1.position[0], plane1.position[1], plane1.position[2], COLOR_GREEN));
    }
    if (bomb_shoot && bom%13 == 0)
    {
        bomb.push_back(Bomb(plane1.position[0], plane1.position[1], plane1.position[2], COLOR_BLACK));
    }
    if (state2 && bom%13 == 0)
    {
        bomb.push_back(Bomb(plane1.position[0], plane1.position[1], plane1.position[2], COLOR_BLACK));
    }
    if(barrel_roll)
    {
        rolls = 360;
        // for (int i = 0; i < 720; ++i)
        // {
        //     plane1.barrel_roll();
            
        // }
    }
    for (int i = 0; i < canon.size(); ++i)
    {
        if(detect_collision(plane1.plane_bbox, canon[i].canon_bbox) && bom%13 == 0 && canon[i].vis == 1)
        {
            // printf("Attackkkkk\n");
            missile.push_back(Missile(canon[i].position[0],canon[i].position[1],canon[i].position[2],COLOR_RED,plane1.position));

        }
    }

    for (int i = 0; i < checkpoint.size(); ++i)
    {
        if(detect_collision(plane1.plane_bbox, checkpoint[i].checkpoint_bbox) && bom%13 == 0 && checkpoint[i].vis == 1)
        {
            // printf("Attackkkkk\n");
            missile.push_back(Missile(checkpoint[i].position[0],checkpoint[i].position[1],checkpoint[i].position[2],COLOR_RED,plane1.position));

        }
    }
    if(rolls > 0)
    {
        plane1.barrel_roll();
        rolls --;
    }
    // for (int i = 0; i < missile.size(); ++i)
    // {
    //     missile[i].target.x = plane1.position.x;
    //     missile[i].target.y = plane1.position.y;
    //     missile[i].target.z = plane1.position.z;
    // }
    //Camera views
    one  = glfwGetKey(window, GLFW_KEY_1);
    two = glfwGetKey(window, GLFW_KEY_2);
    three  = glfwGetKey(window, GLFW_KEY_3);
    four = glfwGetKey(window, GLFW_KEY_4);

    glfwSetScrollCallback(window, scroll_callback);
    bom ++;
}

void tick_elements() {
    plane1.tick();
    // missile.tick();
    camera_rotation_angle += 1;
    for (int i = 0; i < pmissile.size(); ++i)
    {
        pmissile[i].tick();
    }
    for (int i = 0; i < canon.size(); ++i)
    {
        canon[i].tick();
    }
    for (int i = 0; i < bomb.size(); ++i)
    {
        bomb[i].tick();
    }
    for (int i = 0; i < missile.size(); ++i)
    {
        missile[i].tick();
    }
    for (int i = 0; i < parachute.size(); ++i)
    {
        if((plane1.position.z - parachute[i].position.z) < 10)
        {
            // printf("Fall\n");
            parachute[i].tick();
        }
    }
    dashboard_fuel.tick(plane1.fuel*180/10000);
    dashboard_altitude.tick(plane1.altitude*180/100);
    dashboard_speed.tick(plane1.speed*180/20);
    compass.tick(plane1.position);

    display1.number = score%10;
    display2.number = (score/10)%10;
    display3.number = (score/100)%10;
    display4.number = (score/1000)%10;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    plane1       = Plane(0, 0, 0, COLOR_GREY);
    ground       = Ground(0, -20, 0, COLOR_SEA);
    dashboard_altitude    = Dashboard(plane1.position.x, plane1.position.y + 10, plane1.position.z - 5, COLOR_RED, (plane1.altitude*180)/100);
    dashboard_fuel    = Dashboard(plane1.position.x, plane1.position.y + 10, plane1.position.z - 5, COLOR_RED, (plane1.fuel*180)/100000);
    dashboard_speed    = Dashboard(plane1.position.x, plane1.position.y + 10, plane1.position.z - 5, COLOR_RED, (plane1.speed*180));
    compass      = Compass(0, 0, 0, COLOR_RED);
    display1     = Display(0,0,0,COLOR_BLACK);
    display2     = Display(0,0,0,COLOR_BLACK);
    display3     = Display(0,0,0,COLOR_BLACK);
    display4     = Display(0,0,0,COLOR_BLACK);
    // arrow        = Arrow(0, 5, -10, COLOR_GREEN);

    // printf("%f %f %f\n",dashboard.position.x, dashboard.position.y, dashboard.position.z );
    // printf("Plane - %f %f %f\n",plane1.position.x, plane1.position.y, plane1.position.z );
    // missile      = Missile(20, -20, -80, COLOR_RED);
    //Missile
    // for (int i = 0; i < missile.size(); ++i)
    // {
    //     missile[i].target.x = plane1.position.x;
    //     missile[i].target.y = plane1.position.y;
    //     missile[i].target.z = plane1.position.z;
    // }
    
    for (int i = 0; i < 2000; i+=20)
    {
        float n1 = rand() % 100 -50;
        float n2 = rand() % 20 -5;
        ring.push_back(Ring(n1, n2, -i, COLOR_RED));
    }

    for (int i = 0; i < 500; i++)
    {
        float n1 = rand() % 4000 -2000;
        float n2 = rand() % 4000 -2000;
        volcano.push_back(Volcano(n1, -20, n2, COLOR_BROWN));
    }

    for (int i = 0; i < 2000; i+=100)
    {
        float n1 = rand() % 200 -100;
        canon.push_back(Canon(n1, -20, -i, COLOR_RED));
    }

    for (int i = 0; i < 2000; i+=50)
    {
        float n1 = rand() % 100 -50;
        float n2 = rand() % 20 -5;
        fuel.push_back(Fuel(n1, n2, -i, COLOR_YELLOW));
    }
    int r = 1;
    for (int i = 20; i < 2000; i+=100)
    {
        parachute.push_back(Parachute(0, 30, -i, COLOR_BLACK));
        r++;
    }
    for (int i = 100; i <= 2000; i+=500)
    {
        arrow.push_back(Arrow(0, 0, -i, COLOR_GREEN));
    }
    
    for (int i = 100; i <= 2000; i+=500)
    {
        checkpoint.push_back(Checkpoint(0, -20, -i, COLOR_GREEN));
    }
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP"); 
    ortho_projection.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
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
            for (int i = 0; i < ring.size(); ++i)
            {
                if (detect_collision(plane1.plane_bbox, ring[i].ring_bbox) && ring[i].vis == 0)
                {
                    score += 10;
                    printf("BONUS BITCHES\n");
                    ring[i].vis = 1;
                }
            }
            if(bom%13 == 0)
                score ++;
            for (int i = 0; i < volcano.size(); ++i)
            {
                 if(detect_collision(plane1.plane_bbox, volcano[i].volcano_bbox))
                {
                    plane1.health --;
                    // quit(window);
                    printf("DEDDDDD\n");
                }
            }
            //make changes&&&&&&&&&&&&&&&&
            if (detect_collision(plane1.plane_bbox, arrow[t].arrow_bbox) && checkpoint[t].vis == 0)
            {
                printf("Next cHeckpoint\n");
                t++;
                score += 100;
            }
            if(plane1.fuel == 0 || plane1.altitude < -20)
                quit(window);
            for (int i = 0; i < fuel.size(); ++i)
            {
                if(detect_collision(plane1.plane_bbox, fuel[i].fuel_bbox) && fuel[i].collected == 0)
                {
                    printf("Fuel up\n");
                    plane1.fuel += 1000;
                    fuel[i].collected = 1;
                }
            }
            for (int i = 0; i < canon.size(); ++i)
            {
                for (int j = 0; j < bomb.size(); ++j)
                {
                    if(detect_collision(bomb[j].bomb_bbox, canon[i].canon_bbox2) && canon[i].vis == 1)
                    {
                        printf("Canon gone\n");
                        canon[i].vis = 0;
                    }
                }
            }
            for (int i = 0; i < checkpoint.size(); ++i)
            {
                for (int j = 0; j < bomb.size(); ++j)
                {
                    if(detect_collision(bomb[j].bomb_bbox, checkpoint[i].checkpoint_bbox2) && checkpoint[i].vis == 1)
                    {
                        printf("checkpoint gone\n");
                        checkpoint[i].vis = 0;
                    }
                }
            }
            for (int i = 0; i < missile.size(); ++i)
            {
               if (detect_collision(plane1.plane_bbox, missile[i].missile_bbox) && missile[i].timer < 100)
               {
                   plane1.health --;
                   printf("%f\n",plane1.health );
               }
            }
            for (int i = 0; i < parachute.size(); ++i)
            {
                for (int j = 0; j < pmissile.size(); ++j)
                {
                    if(detect_collision(parachute[i].parachute_bbox, pmissile[j].pmissile_bbox) && parachute[i].vis == 1)
                    {
                        printf("Die Parachute\n");
                        parachute[i].vis = 0;
                    }
                }
            }
            // for (int i = 0; i < canon.size(); ++i)
            // {
            //      if(detect_collision(plane1.plane_bbox, canon[i].canon_bbox))
            //     {
            //         printf("Attackkkkk\n"); 

            //     }
            // }
            // printf("%f %f %f\n",dashboard.position.x, dashboard.position.y, dashboard.position.z );
            // printf("Plane - %f %f %f\n",plane1.position.x, plane1.position.y, plane1.position.z );
            // dashboard.position.x = eye.x;
            // dashboard.position.y = eye.y;
            // dashboard.position.z = eye.z;

        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height) &&
            abs(a.z - b.z) * 2 < (a.depth + b.depth));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    ortho_projection.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    Matrices.projection = glm::perspective(90.0f, 1.0f, 0.1f, 1000.0f);
}
