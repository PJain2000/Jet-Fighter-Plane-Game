#include "checkpoint.h"
#include "main.h"

Checkpoint::Checkpoint(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    this->vis = 1;

    this->checkpoint_bbox.height = 200;
    this->checkpoint_bbox.width = 200;
    this->checkpoint_bbox.depth = 30;
    this->checkpoint_bbox.x = x;
    this->checkpoint_bbox.y = y;
    this->checkpoint_bbox.z = z;

    this->checkpoint_bbox2.height = 5;
    this->checkpoint_bbox2.width = 5;
    this->checkpoint_bbox2.depth = 5;
    this->checkpoint_bbox2.x = x;
    this->checkpoint_bbox2.y = y;
    this->checkpoint_bbox2.z = z;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int n = 100;
    
    double theta = (2 * M_PI)/n;

    int k = 0,j = 0;
    GLfloat vertex_buffer_data1[18*n];
    for (int i = 0; i < n; ++i)
    {
        vertex_buffer_data1[k++] =  cos(i*theta) * 1.0f;
        vertex_buffer_data1[k++] = sin(i*theta) * 1.0f + 1.0f;
        vertex_buffer_data1[k++] = 1.0f;
        
        vertex_buffer_data1[k++] = cos((i+1)*theta) * 1.0f;
        vertex_buffer_data1[k++] = sin((i+1)*theta) * 1.0f + 1.0f;
        vertex_buffer_data1[k++] = 1.0f;
        
        vertex_buffer_data1[k++] = cos((j+1)*theta)  * 0.5f;
        vertex_buffer_data1[k++] = sin((j+1)*theta)  * 0.5f + 1.0f;
        vertex_buffer_data1[k++] = -1.0f;

        vertex_buffer_data1[k++] =  cos((j+1)*theta)  * 0.5f;
        vertex_buffer_data1[k++] = sin((j+1)*theta)  * 0.5f + 1.0f;
        vertex_buffer_data1[k++] = -1.0f;
        
        vertex_buffer_data1[k++] = cos(i*theta) * 1.0f;
        vertex_buffer_data1[k++] = sin(i*theta) * 1.0f + 1.0f;
        vertex_buffer_data1[k++] = 1.0f;
        
        vertex_buffer_data1[k++] = cos((j)*theta)  * 0.5f;
        vertex_buffer_data1[k++] = sin((j)*theta)  * 0.5f + 1.0f;
        vertex_buffer_data1[k++] = -1.0f;

        j++;
    }

    static const GLfloat vertex_buffer_data2[] = {
        4.0f, 0.1f, -4.0f, // triangle 1 : begin
        -4.0f, 0.1f, -4.0f,
        -4.0f, 0.1f, 4.0f, // triangle 1 : end
        -4.0f, 0.1f, 4.0f, // triangle 2 : begin
        4.0f, 0.1f, -4.0f,
        4.0f, 0.1f, 4.0f, // triangle 2 : end
    };

    int l = 0;
    GLfloat vertex_buffer_data3[9*n];
    for (int i = 0; i < n; i++) 
    {
        vertex_buffer_data3[l++] =  0.0f;
        vertex_buffer_data3[l++] = 1.0f;
        vertex_buffer_data3[l++] = -1.0f;
        
        vertex_buffer_data3[l++] = cos(i*theta) * 0.5f;
        vertex_buffer_data3[l++] = sin(i*theta) * 0.5f + 1.0f;
        vertex_buffer_data3[l++] = -1.0f;
        
        vertex_buffer_data3[l++] = cos((i+1)*theta) * 0.5f;
        vertex_buffer_data3[l++] = sin((i+1)*theta)  * 0.5f + 1.0f;
        vertex_buffer_data3[l++] = -1.0f;
    }
    this->object1 = create3DObject(GL_TRIANGLES, 200*3, vertex_buffer_data1, COLOR_BLACK, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_RED, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 200*3, vertex_buffer_data3, COLOR_BLACK, GL_FILL);
}

void Checkpoint::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->vis == 1)
    {
        draw3DObject(this->object1);
        draw3DObject(this->object2);
        draw3DObject(this->object3);
    }
}

void Checkpoint::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Checkpoint::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

