#include "main.h"

#ifndef DISPLAY_H
#define DISPLAY_H


class Display {
public:
	Display() {}
    Display(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void tick();
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    int number;
    glm::mat4 display_coord;
    void move_forward();
    void tilt_left();
    void tilt_right();
    void roll_clk();
    void roll_aclk();
    void pitch_up();
    void pitch_down();
    float rotate;
    float tilt;
    double speed;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
    VAO *object7;

};

#endif // DISPLAY_H
