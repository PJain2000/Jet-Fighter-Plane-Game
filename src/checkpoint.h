#include "main.h"

#ifndef CHECKPOINT_H
#define CHECKPOINT_H


class Checkpoint {
public:
    Checkpoint() {}
    Checkpoint(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    bounding_box_t checkpoint_bbox;
    bounding_box_t checkpoint_bbox2;
    double speed;
    int vis;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;

};

#endif // CHECKPOINT_H