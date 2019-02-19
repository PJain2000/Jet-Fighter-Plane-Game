#include "volcano.h"
#include "main.h"

Volcano::Volcano(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;

    this->volcano_bbox.height = 10;
    this->volcano_bbox.width = 50;
    this->volcano_bbox.depth = 10;
    this->volcano_bbox.x = x;
    this->volcano_bbox.y = y+10;
    this->volcano_bbox.z = z;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int n = 100;
    
    double theta = (2 * M_PI)/n;

    int k = 0,j = 0;
    GLfloat vertex_buffer_data1[9*n];
    for (int i = 0; i < n; ++i)
    {
        vertex_buffer_data1[k++] =  cos(i*theta) * 3.0f;
        vertex_buffer_data1[k++] = 6.0f;
        vertex_buffer_data1[k++] = sin(i*theta) * 3.0f;
        
        vertex_buffer_data1[k++] = cos((i+1)*theta) * 3.0f;
        vertex_buffer_data1[k++] = 6.0f;
        vertex_buffer_data1[k++] = sin((i+1)*theta) * 3.0f;
        
        vertex_buffer_data1[k++] = cos((j+1)*theta)  * 9.0f;
        vertex_buffer_data1[k++] = 0.0f;
        vertex_buffer_data1[k++] = sin((j+1)*theta)  * 9.0f;

        // vertex_buffer_data1[k++] =  cos((j+1)*theta)  * 3.0f;
        // vertex_buffer_data1[k++] = 0.0f;
        // vertex_buffer_data1[k++] = sin((j+1)*theta)  * 3.0f;
        
        // vertex_buffer_data1[k++] = cos(i*theta) * 1.0f;
        // vertex_buffer_data1[k++] = 2.0f;
        // vertex_buffer_data1[k++] = sin(i*theta) * 1.0f;
        
        // vertex_buffer_data1[k++] = cos((j)*theta)  * 3.0f;
        // vertex_buffer_data1[k++] = 0.0f;
        // vertex_buffer_data1[k++] = sin((j)*theta)  * 3.0f;

        j++;
    }

    int l = 0;
    GLfloat vertex_buffer_data2[9*n];
    for (int i = 0; i < n; i++) 
    {
        vertex_buffer_data2[l++] =  0.0f;
        vertex_buffer_data2[l++] = 0.0f;
        vertex_buffer_data2[l++] = 0.0f;
        
        vertex_buffer_data2[l++] = cos(i*theta) * 4.0f;
        vertex_buffer_data2[l++] = 0.0f;
        vertex_buffer_data2[l++] = sin(i*theta) * 4.0f;
        
        vertex_buffer_data2[l++] = cos((i+1)*theta) * 4.0f;
        vertex_buffer_data2[l++] = 0.0f;
        vertex_buffer_data2[l++] = sin((i+1)*theta)  * 4.0f;
    }

    int m = 0;
    GLfloat vertex_buffer_data3[9*n];
    for (int i = 0; i < n; i++) 
    {
        vertex_buffer_data3[m++] =  0.0f;
        vertex_buffer_data3[m++] = 6.0f;
        vertex_buffer_data3[m++] = 0.0f;
        
        vertex_buffer_data3[m++] = cos(i*theta) * 3.0f;
        vertex_buffer_data3[m++] = 6.0f;
        vertex_buffer_data3[m++] = sin(i*theta) * 3.0f;
        
        vertex_buffer_data3[m++] = cos((i+1)*theta) * 3.0f;
        vertex_buffer_data3[m++] = 6.0f;
        vertex_buffer_data3[m++] = sin((i+1)*theta)  * 3.0f;
    }

    this->object1 = create3DObject(GL_TRIANGLES, 100*3, vertex_buffer_data1, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 100*3, vertex_buffer_data2, COLOR_VLAND, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 100*3, vertex_buffer_data3, COLOR_ORANGE, GL_FILL);
}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    // draw3DObject(this->object2);
    draw3DObject(this->object3);
}

void Volcano::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Volcano::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

