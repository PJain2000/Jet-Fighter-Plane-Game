#include "main.h"

#ifndef PMISSILE_H
#define PMISSILE_H


class PMissile {
public:
    PMissile() {}
    PMissile(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    bounding_box_t pmissile_bbox;
    double speed;
    int timer;
    
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;

};

#endif // PMISSILE_H