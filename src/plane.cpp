#include "plane.h"
#include "main.h"
#include <math.h>

Plane::Plane(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    // this->rotation = 0;
    this->tilt = 0.1;
    this->rotate = 0.5;
    speed = 0.3;
    this->health = 100;
    this->coord = glm::mat4(1.0f);
    this->fuel = 10000;

    this->plane_bbox.height = 3;
    this->plane_bbox.width = 9;
    this->plane_bbox.depth = 3;
    this->plane_bbox.x = x;
    this->plane_bbox.y = y;
    this->plane_bbox.z = z;

    int n = 100;
    
    double theta = (2 * M_PI)/n;

    int k = 0,j = 0;
    GLfloat vertex_buffer_data1[18*n];
    for (int i = 0; i < n; ++i)
    {
        vertex_buffer_data1[k++] =  cos(i*theta) * 1.2f;
        vertex_buffer_data1[k++] = sin(i*theta) * 1.2f;
        vertex_buffer_data1[k++] = 1.0f;
        
        vertex_buffer_data1[k++] = cos((i+1)*theta) * 1.2f;
        vertex_buffer_data1[k++] = sin((i+1)*theta) * 1.2f;
        vertex_buffer_data1[k++] = 1.0f;
        
        vertex_buffer_data1[k++] = cos((j+1)*theta)  * 1.0f;
        vertex_buffer_data1[k++] = sin((j+1)*theta)  * 1.0f;
        vertex_buffer_data1[k++] = -1.0f;

        vertex_buffer_data1[k++] =  cos((j+1)*theta)  * 1.0f;
        vertex_buffer_data1[k++] = sin((j+1)*theta)  * 1.0f;
        vertex_buffer_data1[k++] = -1.0f;
        
        vertex_buffer_data1[k++] = cos(i*theta) * 1.2f;
        vertex_buffer_data1[k++] = sin(i*theta) * 1.2f;
        vertex_buffer_data1[k++] = 1.0f;
        
        vertex_buffer_data1[k++] = cos((j)*theta)  * 1.0f;
        vertex_buffer_data1[k++] = sin((j)*theta)  * 1.0f;
        vertex_buffer_data1[k++] = -1.0f;

        j++;
    }

    int l = 0;
    GLfloat vertex_buffer_data2[9*n];
    for (int i = 0; i < n; i++) 
    {
        vertex_buffer_data2[l++] =  0.0f;
        vertex_buffer_data2[l++] = 0.0f;
        vertex_buffer_data2[l++] = 1.0f;
        
        vertex_buffer_data2[l++] = cos(i*theta) * 1.0f;
        vertex_buffer_data2[l++] = sin(i*theta) * 1.0f;
        vertex_buffer_data2[l++] = 1.0f;
        
        vertex_buffer_data2[l++] = cos((i+1)*theta) * 1.0f;
        vertex_buffer_data2[l++] = sin((i+1)*theta)  * 1.0f;
        vertex_buffer_data2[l++] = 1.0f;
    }

    static const GLfloat vertex_buffer_data3[] = {
        0.0f, 0.0f, 0.0f, // triangle 1 : begin
        0.0f, 0.0f, -0.5f,
        4.5f, 0.0f, -0.5f, // triangle 1 : end
        // 0.0f, 0.0f, -0.5f, // triangle 2 : begin
        // 2.5f, 0.0f, 0.5f,
        // 1.5f, 0.0f, -0.5f, // triangle 2 : end
    };

    static const GLfloat vertex_buffer_data4[] = {
        0.0f, 0.0f, 0.0f, // triangle 1 : begin
        0.0f, 0.0f, -0.5f,
        -4.5f, 0.0f, -0.5f, // triangle 1 : end
        // 0.0f, 0.0f, -0.5f, // triangle 2 : begin
        // -2.5f, 0.0f, 0.5f,
        // -1.5f, 0.0f, -0.5f, // triangle 2 : end
    };

    static const GLfloat vertex_buffer_data5[] = {
        0.0f, 0.0f, 0.0f, // triangle 1 : begin
        0.0f, 0.0f, 1.0f,
        0.0f, 2.0f, 1.0f, // triangle 1 : end
        0.0f, 2.0f, 1.0f, // triangle 2 : begin
        0.0f, 0.0f, 0.0f,
        0.0f, 2.0f, 0.75f, // triangle 2 : end
    };

    static const GLfloat vertex_buffer_data6[] = {
        1.0f, 0.0f, 1.0f, // triangle 1 : begin
        1.0f, 0.0f, 0.75f,
        1.5f, -1.0f, 1.0f, // triangle 1 : end
    };

    static const GLfloat vertex_buffer_data7[] = {
        -1.0f, 0.0f, 1.0f, // triangle 1 : begin
        -1.0f, 0.0f, 0.75f,
        -1.5f, -1.0f, 1.0f, // triangle 1 : end
    };

    int m = 0;
    GLfloat vertex_buffer_data8[9*n];
    for (int i = 0; i < n; ++i)
    {
        vertex_buffer_data8[m++] =  0.0f;
        vertex_buffer_data8[m++] = 0.0f;
        vertex_buffer_data8[m++] = -2.0f;
        
        vertex_buffer_data8[m++] = cos(i*theta) * 1.0f;
        vertex_buffer_data8[m++] = sin(i*theta) * 1.0f;
        vertex_buffer_data8[m++] = -1.0f;
        
        vertex_buffer_data8[m++] = cos((i+1)*theta) * 1.0f;
        vertex_buffer_data8[m++] = sin((i+1)*theta)  * 1.0f;
        vertex_buffer_data8[m++] = -1.0f;
    }

    this->object1 = create3DObject(GL_TRIANGLES, 200*3, vertex_buffer_data1, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 100*3, vertex_buffer_data2, color, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data3, COLOR_DGREY, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data4, COLOR_DGREY, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data5, COLOR_DGREY, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data6, COLOR_DGREY, GL_FILL);
    this->object7 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data7, COLOR_DGREY, GL_FILL);
    this->object8 = create3DObject(GL_TRIANGLES, 100*3, vertex_buffer_data8, color, GL_FILL);

    this->object9 = create3DObject(GL_LINES, 200*3, vertex_buffer_data1, COLOR_BLACK, GL_FILL);


}

void Plane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * this->coord);//replace
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    // draw3DObject(this->object6);
    // draw3DObject(this->object7);
    draw3DObject(this->object8);
    draw3DObject(this->object9);
}

void Plane::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Plane::tick() {
    this->position.z -= 0.2*(this->coord[2].z);
    this->position.x -= 0.2*(this->coord[2].x);
    this->position.y -= 0.2*(this->coord[2].y);
    this->plane_bbox.x = this->position.x;
    this->plane_bbox.y = this->position.y;
    this->plane_bbox.z = this->position.z;
    this->altitude = this->position.y;
    this->fuel--;
}

void Plane::move_forward() {
    //move along coord z not actual z
    this->position.x -= speed*(this->coord[2].x);
    this->position.y -= speed*(this->coord[2].y);
    this->position.z -= speed*(this->coord[2].z);
}

void Plane::tilt_left() {
    glm::mat4 rotation = glm::rotate((float) (this->rotate * M_PI / 180.0f), glm::vec3(0, 1, 0));
    this->coord *= rotation;
}

void Plane::tilt_right() {
    glm::mat4 rotation = glm::rotate((float) (-this->rotate * M_PI / 180.0f), glm::vec3(0, 1, 0));
    this->coord *= rotation;
}

void Plane::roll_clk() {
    glm::mat4 rotation = glm::rotate((float) (this->tilt * M_PI / 180.0f), glm::vec3(0, 0, 1));
    this->coord *= rotation;
}

void Plane::roll_aclk() {
    glm::mat4 rotation = glm::rotate((float) (-this->tilt * M_PI / 180.0f), glm::vec3(0, 0, 1));
    this->coord *= rotation;
}

void Plane::pitch_up() {
    glm::mat4 rotation = glm::rotate((float) (this->rotate * M_PI / 180.0f), glm::vec3(1, 0, 0));
    this->coord *= rotation;
}

void Plane::pitch_down() {
    glm::mat4 rotation = glm::rotate((float) (-this->rotate * M_PI / 180.0f), glm::vec3(1, 0, 0));
    this->coord *= rotation;
}

void Plane::barrel_roll() {
        glm::mat4 rotation = glm::rotate((float) (1 * M_PI / 180.0f), glm::vec3(0, 0, 1));
        this->coord *= rotation;
}


