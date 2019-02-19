#include "dashboard.h"
#include "main.h"

Dashboard::Dashboard(float x, float y, float z, color_t color, float angle) {
    this->position = glm::vec3(x, y, z);
    this->rotation = angle;
    speed = 1;
    this->tilt = 0.1;
    this->rotate = 0.5;
    this->dash_coord = glm::mat4(1.0f);
    this->needle = glm::mat4(1.0f);
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // this->needle *= rotate;
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
        
        vertex_buffer_data[l++] = cos(i*theta) * 0.5f;
        vertex_buffer_data[l++] = sin(i*theta) * 0.5f;
        vertex_buffer_data[l++] = 0.0f;
        
        vertex_buffer_data[l++] = cos((i+1)*theta) * 0.5f;
        vertex_buffer_data[l++] = sin((i+1)*theta)  * 0.5f;
        vertex_buffer_data[l++] = 0.0f;
    }

    l = 0;
    GLfloat vertex_buffer_data2[9*n];
    for (int i = 0; i < n; i++) 
    {
        vertex_buffer_data2[l++] =  0.0f;
        vertex_buffer_data2[l++] = 0.0f;
        vertex_buffer_data2[l++] = 0.0001f;
        
        vertex_buffer_data2[l++] = cos(i*theta) * 0.4f;
        vertex_buffer_data2[l++] = sin(i*theta) * 0.4f;
        vertex_buffer_data2[l++] = 0.0001f;
        
        vertex_buffer_data2[l++] = cos((i+1)*theta) * 0.4f;
        vertex_buffer_data2[l++] = sin((i+1)*theta)  * 0.4f;
        vertex_buffer_data2[l++] = 0.0001f;
    }

    static const GLfloat vertex_buffer_data3[] = {
        0.4f, 0.0f, 0.01f, // triangle 1 : begin
        0.0f, 0.01f, 0.01f,
        0.0f, -0.01f, 0.01f, // triangle 1 : end
    };

    

    this->object = create3DObject(GL_TRIANGLES, 100*3, vertex_buffer_data, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 100*3, vertex_buffer_data2, COLOR_SEA, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data3, color, GL_FILL);
}

void Dashboard::draw(glm::mat4 ortho_VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // this->dash_coord *= rotate;
    Matrices.model *= (translate * this->dash_coord);
    glm::mat4 MVP = ortho_VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);

    Matrices.model    *= glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    MVP = ortho_VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object3);
}

void Dashboard::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Dashboard::tick(float angle) {
    this->rotation = angle;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
void Dashboard::move_forward() {
    //move along coord z not actual z
    this->position.x -= speed*(this->dash_coord[2].x);
    this->position.y -= speed*(this->dash_coord[2].y);
    this->position.z -= speed*(this->dash_coord[2].z);
}
void Dashboard::tilt_left() {
    glm::mat4 rotation = glm::rotate((float) (this->rotate * M_PI / 180.0f), glm::vec3(0, 1, 0));
    this->dash_coord *= rotation;
}

void Dashboard::tilt_right() {
    glm::mat4 rotation = glm::rotate((float) (-this->rotate * M_PI / 180.0f), glm::vec3(0, 1, 0));
    this->dash_coord *= rotation;
}

void Dashboard::roll_clk() {
    glm::mat4 rotation = glm::rotate((float) (this->tilt * M_PI / 180.0f), glm::vec3(0, 0, 1));
    this->dash_coord *= rotation;
}

void Dashboard::roll_aclk() {
    glm::mat4 rotation = glm::rotate((float) (-this->tilt * M_PI / 180.0f), glm::vec3(0, 0, 1));
    this->dash_coord *= rotation;
}

void Dashboard::pitch_up() {
    glm::mat4 rotation = glm::rotate((float) (this->rotate * M_PI / 180.0f), glm::vec3(1, 0, 0));
    this->dash_coord *= rotation;
}

void Dashboard::pitch_down() {
    glm::mat4 rotation = glm::rotate((float) (-this->rotate * M_PI / 180.0f), glm::vec3(1, 0, 0));
    this->dash_coord *= rotation;
}