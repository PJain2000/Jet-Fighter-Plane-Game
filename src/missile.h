#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H


class Missile {
public:
    Missile() {}
    Missile(float x, float y, float z, color_t color, glm::vec3 plane);
    glm::vec3 position;
    glm::vec3 target;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    bounding_box_t missile_bbox;
    double speed;
    int timer;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;

};

#endif // MISSILE_H