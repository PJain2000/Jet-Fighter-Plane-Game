#include "compass.h"
#include "main.h"
#include <math.h>

Compass::Compass(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    this->tilt = 0.1;
    this->rotate = 0.5;
    this->dash_coord = glm::mat4(1.0f);
    this->angle = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int n = 100;
    
    double theta = (2 * M_PI)/n;

    int l = 0;
    GLfloat vertex_buffer_data[9*n];
    for (int i = 0; i < n; i++) 
    {
        vertex_buffer_data[l++] =  0.0f;
        vertex_buffer_data[l++] = 0.0f;
        vertex_buffer_data[l++] = 0.0f;
        
        vertex_buffer_data[l++] = cos(i*theta) * 1.0f;
        vertex_buffer_data[l++] = sin(i*theta) * 1.0f;
        vertex_buffer_data[l++] = 0.0f;
        
        vertex_buffer_data[l++] = cos((i+1)*theta) * 1.0f;
        vertex_buffer_data[l++] = sin((i+1)*theta)  * 1.0f;
        vertex_buffer_data[l++] = 0.0f;
    }

    static const GLfloat vertex_buffer_data2[] = {
        0.0f, 1.0f, 0.01f, // triangle 1 : begin
        0.1f, 0.0f, 0.01f,
        -0.1f, 0.0f, 0.01f, // triangle 1 : end
    };

    static const GLfloat vertex_buffer_data3[] = {
        0.0f, -1.0f, 0.01f, // triangle 1 : begin
        0.1f, 0.0f, 0.01f,
        -0.1f, 0.0f, 0.01f, // triangle 1 : end
    };

    this->object = create3DObject(GL_TRIANGLES, 100*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data2, COLOR_RED, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data3, COLOR_SEA, GL_FILL);
}

void Compass::draw(glm::mat4 ortho_VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * this->dash_coord);
    glm::mat4 MVP = ortho_VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

    Matrices.model    *= glm::rotate((float) (this->angle * M_PI / 180.0f), glm::vec3(0, 0, 1));
    MVP = ortho_VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
}

void Compass::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Compass::tick(glm::vec3 plane) {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
    glm::vec3 v = glm::vec3(0.0, 0.0, -2000.0);
    glm::vec3 u = v - plane;
    glm::vec3 w = glm::normalize(u);
    glm::vec3 x = glm::vec3(0.0, 0.0, -1.0);
    this->angle = acos(-w.z)*1000;
    // printf("%f\n", this->angle);
    // angle = 60;
}
void Compass::move_forward() {
    //move along coord z not actual z
    this->position.x -= speed*(this->dash_coord[2].x);
    this->position.y -= speed*(this->dash_coord[2].y);
    this->position.z -= speed*(this->dash_coord[2].z);
}
void Compass::tilt_left() {
    glm::mat4 rotation = glm::rotate((float) (this->rotate * M_PI / 180.0f), glm::vec3(0, 1, 0));
    this->dash_coord *= rotation;
}

void Compass::tilt_right() {
    glm::mat4 rotation = glm::rotate((float) (-this->rotate * M_PI / 180.0f), glm::vec3(0, 1, 0));
    this->dash_coord *= rotation;
}

void Compass::roll_clk() {
    glm::mat4 rotation = glm::rotate((float) (this->tilt * M_PI / 180.0f), glm::vec3(0, 0, 1));
    this->dash_coord *= rotation;
}

void Compass::roll_aclk() {
    glm::mat4 rotation = glm::rotate((float) (-this->tilt * M_PI / 180.0f), glm::vec3(0, 0, 1));
    this->dash_coord *= rotation;
}

void Compass::pitch_up() {
    glm::mat4 rotation = glm::rotate((float) (this->rotate * M_PI / 180.0f), glm::vec3(1, 0, 0));
    this->dash_coord *= rotation;
}

void Compass::pitch_down() {
    glm::mat4 rotation = glm::rotate((float) (-this->rotate * M_PI / 180.0f), glm::vec3(1, 0, 0));
    this->dash_coord *= rotation;
}