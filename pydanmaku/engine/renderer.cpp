#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <list>
#include <stdbool.h>
#include "bullet.h"

#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;

#include <FreeImage.h>
#include "common/shader.h"
#include "common/png.h"
#include "common/trig.h"

#include "renderer.h"

#define WIDTH 640
#define HEIGHT 480
#define XU 2.0/WIDTH
#define YU 2.0/HEIGHT
#define AMULET "./amulet.png"

GLFWwindow* window;
bool render_inited = false;

GLuint shader;
BYTE* amuletImage;
int w=0, h=0;

GLuint vao, vbo, eab;

int last_size=0;

GLfloat *vertices_position;
GLuint *indices;
GLfloat *texture_coord;

void initialize_quads(GLfloat vertices_position[], GLuint indices[], GLfloat texture_coord[], int count) {
    // Use a Vertex Array Object


    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    // Create a Vector Buffer Object that will store the vertices on video memory
    glGenBuffers(1, &vbo);
    // Allocate space for vertex positions and texture coordinates
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 16*count*sizeof(GLfloat), NULL, GL_STATIC_DRAW);

    // Transfer the vertex positions:
    glBufferSubData(GL_ARRAY_BUFFER, 0, 8*count*sizeof(GLfloat), vertices_position);
    // Transfer the texture coordinates:
    glBufferSubData(GL_ARRAY_BUFFER, 8*count*sizeof(GLfloat), 8*count*sizeof(GLfloat), texture_coord);

    // Create an Element Array Buffer that will store the indices array:
    glGenBuffers(1, &eab);

    // Transfer the data from indices to eab
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eab);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*count*sizeof(GLuint), indices, GL_STATIC_DRAW);

    // Create a texture
    GLuint texture;
    glGenTextures(1, &texture);
    // Specify that we work with a 2D texture
    glBindTexture(GL_TEXTURE_2D, texture);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
    // start load_image
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, amuletImage);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // end load_image
    // Get the location of the attributes that enters in the vertex shader
    GLint position_attribute = glGetAttribLocation(shader, "position");

    // Specify how the data for position can be accessed
    glVertexAttribPointer(position_attribute, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // Enable the attribute
    glEnableVertexAttribArray(position_attribute);

    // Texture coord attribute
    GLint texture_coord_attribute = glGetAttribLocation(shader, "texture_coord");
    glVertexAttribPointer(texture_coord_attribute, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(8*count*sizeof(GLfloat)));
    glEnableVertexAttribArray(texture_coord_attribute);
    
}

void apply_angle(double *x, double *y, double angle){
    double c = l_cos(angle);
    double s = l_sin(angle);
    double nx = (*x)*c - (*y)*s;
    double ny = (*x)*s + (*y)*c;
    *x = nx;
    *y = ny;
}

void add_quad(GLfloat vert[], GLuint ind[], GLfloat tex[], int i, double x, double y, double h, double w, double angle){
    double coords[8] = {
         -w/2.0, -h/2.0,
          w/2.0, -h/2.0,
          w/2.0,  h/2.0,
         -w/2.0,  h/2.0,
    };
    for (int j=0; j<8; j+=2){
        apply_angle(&(coords[j]), &(coords[j+1]), angle);
        vert[8*i+j]   = XU*(coords[j]   + x)-1.0;
        vert[8*i+j+1] = YU*(coords[j+1] + y)-1.0;
    }

    ind[6*i+0] = ind[6*i+5] = 4*i+0;
    ind[6*i+2] = ind[6*i+3] = 4*i+2;
    ind[6*i+1] =              4*i+1;
    ind[6*i+4] =              4*i+3;

    tex[8*i+0] = tex[8*i+1] = tex[8*i+3] = tex[8*i+6] = 0.0;
    tex[8*i+2] = tex[8*i+4] = tex[8*i+5] = tex[8*i+7] = 1.0;
}

void renderer_init() {
    trig_init();
    glfwInit();
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "PyDanmaku", NULL, NULL);

    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    shader = create_program("shaders/vert.shader", "shaders/frag.shader");
    amuletImage = load_image(AMULET, &w, &h);

    render_inited = true;

}

void render_bullets(std::list<Bullet> *bullets){
    if(!render_inited) return;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    int count = bullets->size();
    if (count > last_size || last_size == 0) {
        delete [] vertices_position;
        delete [] indices;
        delete [] texture_coord;
        vertices_position = new GLfloat[8*count];
        indices = new GLuint[6*count];
        texture_coord = new GLfloat[8*count];
        last_size = count;
    }
    int i = 0;
    for (std::list<Bullet>::iterator b = bullets->begin(); b != bullets->end(); b++){
        add_quad(vertices_position, indices, texture_coord, i, b->x, b->y, h, w, b->angle);
        i++;
    }
    initialize_quads(vertices_position, indices, texture_coord, count);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6*count, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &eab);
    glDeleteVertexArrays(1, &vao);
}

void renderer_close() {
    delete [] vertices_position;
    delete [] indices;
    delete [] texture_coord;
    glfwTerminate();
    render_inited = false;
}
