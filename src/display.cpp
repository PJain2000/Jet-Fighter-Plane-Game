#include "display.h"
#include "main.h"
#include <math.h>
using namespace std;

Display::Display(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->number = 0;
    this->rotation = 0;
    speed = 1;
    this->tilt = 0.1;
    this->rotate = 0.5;
    this->display_coord = glm::mat4(1.0f);
    static GLfloat vertex_buffer_data1[] = {
        -0.08f, -0.02f, 0.0f,
        -0.08f,  0.02f, 0.0f,
         0.08f,  0.02f, 0.0f,
         0.08f,  0.02f, 0.0f,
        -0.08f, -0.02f, 0.0f,
         0.08,  -0.02f, 0.0f,
    };
    static GLfloat vertex_buffer_data2[] = {
        -0.08f, -0.02f+0.2f, 0.0f,
        -0.08f,  0.02f+0.2f, 0.0f,
         0.08f,  0.02f+0.2f, 0.0f,
         0.08f,  0.02f+0.2f, 0.0f,
        -0.08f, -0.02f+0.2f, 0.0f,
         0.08,  -0.02f+0.2f, 0.0f,
    };
    static GLfloat vertex_buffer_data3[] = {
        -0.08f, -0.02f-0.2f, 0.0f,
        -0.08f,  0.02f-0.2f, 0.0f,
         0.08f,  0.02f-0.2f, 0.0f,
         0.08f,  0.02f-0.2f, 0.0f,
        -0.08f, -0.02f-0.2f, 0.0f,
         0.08,  -0.02f-0.2f, 0.0f,
    };
    static GLfloat vertex_buffer_data4[] = {
        -0.02f-0.11f, -0.08f+0.1f, 0.0f,
         0.02f-0.11f, -0.08f+0.1f, 0.0f,
         0.02f-0.11f,  0.08f+0.1f, 0.0f,
         0.02f-0.11f,  0.08f+0.1f, 0.0f,
        -0.02f-0.11f, -0.08f+0.1f, 0.0f,
        -0.02f-0.11f,  0.08f+0.1f,  0.0f,
    };
    static GLfloat vertex_buffer_data5[] = {
        -0.02f+0.11f, -0.08f+0.1f, 0.0f,
         0.02f+0.11f, -0.08f+0.1f, 0.0f,
         0.02f+0.11f,  0.08f+0.1f, 0.0f,
         0.02f+0.11f,  0.08f+0.1f, 0.0f,
        -0.02f+0.11f, -0.08f+0.1f, 0.0f,
        -0.02f+0.11f,  0.08f+0.1f,  0.0f,
    };
    static GLfloat vertex_buffer_data6[] = {
        -0.02f-0.11f, -0.08f-0.1f, 0.0f,
         0.02f-0.11f, -0.08f-0.1f, 0.0f,
         0.02f-0.11f,  0.08f-0.1f, 0.0f,
         0.02f-0.11f,  0.08f-0.1f, 0.0f,
        -0.02f-0.11f, -0.08f-0.1f, 0.0f,
        -0.02f-0.11f,  0.08f-0.1f,  0.0f,
    };
    static GLfloat vertex_buffer_data7[] = {
        -0.02f+0.11f, -0.08f-0.1f, 0.0f,
         0.02f+0.11f, -0.08f-0.1f, 0.0f,
         0.02f+0.11f,  0.08f-0.1f, 0.0f,
         0.02f+0.11f,  0.08f-0.1f, 0.0f,
        -0.02f+0.11f, -0.08f-0.1f, 0.0f,
        -0.02f+0.11f,  0.08f-0.1f,  0.0f,
    };
    this->object1 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data1, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data2, color, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data3, color, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data4, color, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data5, color, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data6, color, GL_FILL);
    this->object7 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data7, color, GL_FILL);

}

void Display::draw(glm::mat4 VP) {
    // printf("draw display\n");
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->display_coord * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * this->display_coord);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->number==2||this->number==3||this->number==4||this->number==5||this->number==6||this->number==8||this->number==9)
        draw3DObject(this->object1);
    if(this->number==0||this->number==2||this->number==3||this->number==5||this->number==6||this->number==7||this->number==8||this->number==9)
        draw3DObject(this->object2);
    if(this->number==0||this->number==2||this->number==3||this->number==5||this->number==6||this->number==8||this->number==9)
        draw3DObject(this->object3);
    if(this->number==0||this->number==4||this->number==5||this->number==6||this->number==8||this->number==9)
        draw3DObject(this->object4);
    if(this->number==0||this->number==1||this->number==2||this->number==3||this->number==4||this->number==7||this->number==8||this->number==9)
        draw3DObject(this->object5);
    if(this->number==0||this->number==2||this->number==6||this->number==8)
        draw3DObject(this->object6);
    if(this->number==0||this->number==1||this->number==3||this->number==4||this->number==5||this->number==6||this->number==7||this->number==8||this->number==9)
        draw3DObject(this->object7);
}

void Display::set_position(float x, float y, float z) {
    // printf("set position display\n");
    this->position = glm::vec3(x, y, z);
}

void Display::tick() {
    this->position.x += 0.05;
}

void Display::move_forward() {
    //move along coord z not actual z
    this->position.x -= speed*(this->display_coord[2].x);
    this->position.y -= speed*(this->display_coord[2].y);
    this->position.z -= speed*(this->display_coord[2].z);
}
void Display::tilt_left() {
    glm::mat4 rotation = glm::rotate((float) (this->rotate * M_PI / 180.0f), glm::vec3(0, 1, 0));
    this->display_coord *= rotation;
}

void Display::tilt_right() {
    glm::mat4 rotation = glm::rotate((float) (-this->rotate * M_PI / 180.0f), glm::vec3(0, 1, 0));
    this->display_coord *= rotation;
}

void Display::roll_clk() {
    glm::mat4 rotation = glm::rotate((float) (this->tilt * M_PI / 180.0f), glm::vec3(0, 0, 1));
    this->display_coord *= rotation;
}

void Display::roll_aclk() {
    glm::mat4 rotation = glm::rotate((float) (-this->tilt * M_PI / 180.0f), glm::vec3(0, 0, 1));
    this->display_coord *= rotation;
}

void Display::pitch_up() {
    glm::mat4 rotation = glm::rotate((float) (this->rotate * M_PI / 180.0f), glm::vec3(1, 0, 0));
    this->display_coord *= rotation;
}

void Display::pitch_down() {
    glm::mat4 rotation = glm::rotate((float) (-this->rotate * M_PI / 180.0f), glm::vec3(1, 0, 0));
    this->display_coord *= rotation;
}