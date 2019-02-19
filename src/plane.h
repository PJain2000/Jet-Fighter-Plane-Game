#include "main.h"

#ifndef PLANE_H
#define PLANE_H


class Plane {
public:
    Plane() {}
    Plane(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotate;
    float tilt;
    void draw(glm::mat4 VP);
    float health;
    glm::mat4 coord;
    void set_position(float x, float y, float z);
    void tick();
    
    bounding_box_t plane_bbox;

    void move_forward();
    void tilt_left();
    void tilt_right();
    void roll_clk();
    void roll_aclk();
    void pitch_up();
    void pitch_down();
    void barrel_roll();

    float altitude;
    float fuel;
    double speed;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
    VAO *object7;
    VAO *object8;
    VAO *object9;
};

#endif // PLANE_H
