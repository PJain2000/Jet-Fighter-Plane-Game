#include "main.h"

#ifndef COMPASS_H
#define COMPASS_H


class Compass {
public:
    Compass() {}
    Compass(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float rotate;
    float tilt;
    glm::vec3 target;
    glm::mat4 dash_coord;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick(glm::vec3 plane);
    void move_forward();
    void tilt_left();
    void tilt_right();
    void roll_clk();
    void roll_aclk();
    void pitch_up();
    void pitch_down();
    double speed;
    float angle;
private:
    VAO *object;
    VAO *object2;
    VAO *object3;

};

#endif // COMPASS_H