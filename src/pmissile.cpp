#include "pmissile.h"
#include "main.h"

PMissile::PMissile(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 0.6;
    this->timer = 0;
    // this->coord = u;

    this->pmissile_bbox.height = 2;
    this->pmissile_bbox.width = 2;
    this->pmissile_bbox.depth = 2;
    this->pmissile_bbox.x = x;
    this->pmissile_bbox.y = y;
    this->pmissile_bbox.z = z;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int n = 100;
    
    double theta = (2 * M_PI)/n;
    int j = 0;
    GLfloat vertex_buffer_data1[18*n];
    for (int i = 0; i < n; i++) 
    {
        vertex_buffer_data1[j++] = cos(i*theta) * 0.5f;
        vertex_buffer_data1[j++] = sin(i*theta) * 0.5f;
        vertex_buffer_data1[j++] = 0.5f;
        
        vertex_buffer_data1[j++] = cos((i+1)*theta) * 0.5f;
        vertex_buffer_data1[j++] = sin((i+1)*theta) * 0.5f;
        vertex_buffer_data1[j++] = 0.5f;
        
        vertex_buffer_data1[j++] = cos((i+1)*theta) * 0.5f;
        vertex_buffer_data1[j++] = sin((i+1)*theta) * 0.5f;
        vertex_buffer_data1[j++] = -0.5f;

        vertex_buffer_data1[j++] = cos((i+1)*theta) * 0.5f;
        vertex_buffer_data1[j++] = sin((i+1)*theta) * 0.5f;
        vertex_buffer_data1[j++] = -0.5f;

        vertex_buffer_data1[j++] = cos(i*theta) * 0.5f;
        vertex_buffer_data1[j++] = sin(i*theta) * 0.5f;
        vertex_buffer_data1[j++] = 0.5f;

        vertex_buffer_data1[j++] = cos(i*theta) * 0.5f;
        vertex_buffer_data1[j++] = sin(i*theta) * 0.5f;
        vertex_buffer_data1[j++] = -0.5f;
    }

    int l = 0;
    GLfloat vertex_buffer_data2[9*n];
    for (int i = 0; i < n; i++) 
    {
        vertex_buffer_data2[l++] =  0.0f;
        vertex_buffer_data2[l++] = 0.0f;
        vertex_buffer_data2[l++] = 0.5f;
        
        vertex_buffer_data2[l++] = cos(i*theta) * 0.5f;
        vertex_buffer_data2[l++] = sin(i*theta) * 0.5f;
        vertex_buffer_data2[l++] = 0.5f;
        
        vertex_buffer_data2[l++] = cos((i+1)*theta) * 0.5f;
        vertex_buffer_data2[l++] = sin((i+1)*theta)  * 0.5f;
        vertex_buffer_data2[l++] = 0.5f;
    }

    int m = 0;
    GLfloat vertex_buffer_data3[9*n];
    for (int i = 0; i < n; i++) 
    {
        vertex_buffer_data3[m++] =  0.0f;
        vertex_buffer_data3[m++] = 0.0f;
        vertex_buffer_data3[m++] = -1.0f;
        
        vertex_buffer_data3[m++] = cos(i*theta) * 0.5f;
        vertex_buffer_data3[m++] = sin(i*theta) * 0.5f;
        vertex_buffer_data3[m++] = -0.5f;
        
        vertex_buffer_data3[m++] = cos((i+1)*theta) * 0.5f;
        vertex_buffer_data3[m++] = sin((i+1)*theta)  * 0.5f;
        vertex_buffer_data3[m++] = -0.5f;
    }

    this->object1 = create3DObject(GL_TRIANGLES, 200*3, vertex_buffer_data1, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 100*3, vertex_buffer_data2, color, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 100*3, vertex_buffer_data3, COLOR_BLACK, GL_FILL);
}

void PMissile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(timer < 100)
    {
        draw3DObject(this->object1);
        draw3DObject(this->object2);
        draw3DObject(this->object3);
    }
}

void PMissile::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void PMissile::tick() {
    this->position.z -= speed;
    timer++;
    this->pmissile_bbox.x = this->position.x;
    this->pmissile_bbox.y = this->position.y;
    this->pmissile_bbox.z = this->position.z;
}

