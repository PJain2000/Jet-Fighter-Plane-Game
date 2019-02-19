#include "arrow.h"
#include "main.h"
#include <math.h>

Arrow::Arrow(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 0.3;
    // this->coord = u;

    this->arrow_bbox.height = 2;
    this->arrow_bbox.width = 2;
    this->arrow_bbox.depth = 1;
    this->arrow_bbox.x = x;
    this->arrow_bbox.y = y;
    this->arrow_bbox.z = z;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data1[] = {
        -0.5f, 1.0f, 0.0f, // triangle 1 : begin
        0.5f, 1.0f, 0.0f,
        -0.5f, 0.0f, 0.0f, // triangle 1 : end

        0.5f, 1.0f, 0.0f, // triangle 2 : begin
        -0.5f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f, // triangle 2 : end

        1.0f, 0.0f, 0.0f, // triangle 3 : begin
        -1.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f, // triangle 3 : end
    };
    this->object1 = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data1, color, GL_FILL);
}

void Arrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
}

void Arrow::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Arrow::tick() {
    this->position.y -= speed;
}

