#include "parachute.h"
#include "main.h"
#include <math.h>

Parachute::Parachute(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 0.3;
    this->vis = 1;
    // this->coord = u;

    this->parachute_bbox.height = 3;
    this->parachute_bbox.width = 1;
    this->parachute_bbox.depth = 1;
    this->parachute_bbox.x = x;
    this->parachute_bbox.y = y;
    this->parachute_bbox.z = z;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int n = 100;
    
    double theta = (2 * M_PI)/n;
    double fi = (2 * M_PI)/n;
    int k = 0;
    float r = 0.5;
    GLfloat vertex_buffer_data1[18*n*n];
    for (int i = 0; i < n/2; i++) 
    {
        for (int j = 0; j < n; j++)
        {
            vertex_buffer_data1[k++] = r * cos(i*theta) * cos(j*fi);
            vertex_buffer_data1[k++] = r * sin(i*theta);
            vertex_buffer_data1[k++] = r * cos(i*theta) * sin(j*fi);
            
            vertex_buffer_data1[k++] = r * cos(i*theta) * cos((j+1)*fi);
            vertex_buffer_data1[k++] = r * sin(i*theta);
            vertex_buffer_data1[k++] = r * cos(i*theta) * sin((j+1)*fi);
            
            vertex_buffer_data1[k++] = r * cos((i+1)*theta) * cos(j*fi);
            vertex_buffer_data1[k++] = r * sin((i+1)*theta);
            vertex_buffer_data1[k++] = r * cos((i+1)*theta) * sin(j*fi);

            vertex_buffer_data1[k++] = r * cos(i*theta) * cos((j+1)*fi);
            vertex_buffer_data1[k++] = r * sin(i*theta);
            vertex_buffer_data1[k++] = r * cos(i*theta) * sin((j+1)*fi);

            vertex_buffer_data1[k++] = r * cos((i+1)*theta) * cos(j*fi);
            vertex_buffer_data1[k++] = r * sin((i+1)*theta);
            vertex_buffer_data1[k++] = r * cos((i+1)*theta) * sin(j*fi);

            vertex_buffer_data1[k++] = r * cos((i+1)*theta) * cos((j+1)*fi);
            vertex_buffer_data1[k++] = r * sin((i+1)*theta);
            vertex_buffer_data1[k++] = r * cos((i+1)*theta) * sin((j+1)*fi);
        }
    }

    static const GLfloat vertex_buffer_data2[] = {

        0.5f, 0.0f, 0.0f,
        0.0f, -1.5f, 0.0f,

        -0.5f, 0.0f, 0.0f,
        0.0f, -1.5f, 0.0f,

        0.0f, 0.5f, 0.0f,
        0.0f, -1.5f, 0.0f,

        0.0f, -0.5f, 0.0f,
        0.0f, -1.5f, 0.0f,


    };
    if(this->vis == 1)
    {
        this->object1 = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data1, color, GL_FILL);
        this->object2 = create3DObject(GL_LINES, 8, vertex_buffer_data2, color, GL_FILL);
    }
}

void Parachute::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->position.z < 100)
    {
        draw3DObject(this->object1);
        draw3DObject(this->object2);
    }
}

void Parachute::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Parachute::tick() {
    this->position.y -= 0.2;

    this->parachute_bbox.x = this->position.x;
    this->parachute_bbox.y = this->position.y;
    this->parachute_bbox.z = this->position.z;
}

