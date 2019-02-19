#include "main.h"

#ifndef PARACHUTE_H
#define PARACHUTE_H


class Parachute {
public:
    Parachute() {}
    Parachute(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    bounding_box_t parachute_bbox;
    double speed;
    int vis;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;

};

#endif // PARACHUTE_H