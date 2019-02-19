#include "main.h"

#ifndef RING_H
#define RING_H


class Ring {
public:
    Ring() {}
    Ring(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    bounding_box_t ring_bbox;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
    int vis;
private:
    VAO *object;

};

#endif // RING_H