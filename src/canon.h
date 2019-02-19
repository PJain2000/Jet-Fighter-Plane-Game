#include "main.h"

#ifndef CANON_H
#define CANON_H


class Canon {
public:
    Canon() {}
    Canon(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    bounding_box_t canon_bbox;
    bounding_box_t canon_bbox2;
    double speed;
    int vis;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;

};

#endif // CANON_H