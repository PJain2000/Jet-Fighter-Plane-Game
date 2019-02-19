#include "ring.h"
#include "main.h"

Ring::Ring(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    this->vis = 0;
    this->ring_bbox.height = 6;
    this->ring_bbox.width = 6;
    this->ring_bbox.depth = 0.2;
    this->ring_bbox.x = x;
    this->ring_bbox.y = y;
    this->ring_bbox.z = z;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int n = 100;
    
    double theta = (2 * M_PI)/n;
    int j = 0;
    GLfloat vertex_buffer_data1[18*n];


    for (int i = 0; i < n; i++) 
    {
        vertex_buffer_data1[j++] = cos(i*theta) * 4.0f;
        vertex_buffer_data1[j++] = sin(i*theta) * 4.0f;
        vertex_buffer_data1[j++] = 0.1f;
        
        vertex_buffer_data1[j++] = cos((i+1)*theta) * 4.0f;
        vertex_buffer_data1[j++] = sin((i+1)*theta) * 4.0f;
        vertex_buffer_data1[j++] = 0.1f;
        
        vertex_buffer_data1[j++] = cos((i+1)*theta) * 4.0f;
        vertex_buffer_data1[j++] = sin((i+1)*theta) * 4.0f;
        vertex_buffer_data1[j++] = -0.1f;

        vertex_buffer_data1[j++] = cos((i+1)*theta) * 4.0f;
        vertex_buffer_data1[j++] = sin((i+1)*theta) * 4.0f;
        vertex_buffer_data1[j++] = -0.1f;

        vertex_buffer_data1[j++] = cos(i*theta) * 4.0f;
        vertex_buffer_data1[j++] = sin(i*theta) * 4.0f;
        vertex_buffer_data1[j++] = 0.1f;

        vertex_buffer_data1[j++] = cos(i*theta) * 4.0f;
        vertex_buffer_data1[j++] = sin(i*theta) * 4.0f;
        vertex_buffer_data1[j++] = -0.1f;
    }

    

    this->object = create3DObject(GL_TRIANGLES, 200*3, vertex_buffer_data1, color, GL_FILL);
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->vis == 0)
        draw3DObject(this->object);
}

void Ring::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Ring::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}