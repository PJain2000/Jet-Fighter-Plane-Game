#include "main.h"

#ifndef DASHBOARD_H
#define DASHBOARD_H


class Dashboard {
public:
    Dashboard() {}
    Dashboard(float x, float y, float z, color_t color, float angle);
    glm::vec3 position;
    float rotation;
    float rotate;
    float tilt;
    glm::mat4 dash_coord;
    glm::mat4 needle;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick(float ang);
    void move_forward();
    void tilt_left();
    void tilt_right();
    void roll_clk();
    void roll_aclk();
    void pitch_up();
    void pitch_down();
    double speed;
private:
    VAO *object;
    VAO *object2;
    VAO *object3;

};

#endif // DASHBOARD_H