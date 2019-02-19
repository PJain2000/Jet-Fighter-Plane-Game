#include "main.h"

#ifndef Arrow_H
#define Arrow_H


class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    bounding_box_t arrow_bbox;
    double speed;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;

};

#endif // ARROW_H