#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <list>
#include <stdbool.h>
#include "bullet.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;

#include <FreeImage.h>
#include "common/shader.h"
#include "common/png.h"

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



GLuint initialize_quads(GLfloat vertices_position[], GLuint indices[], GLfloat texture_coord[], int count) {
    // Use a Vertex Array Object

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    // Create a Vector Buffer Object that will store the vertices on video memory
    GLuint vbo;
    glGenBuffers(1, &vbo);
    // Allocate space for vertex positions and texture coordinates
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 8*count + 8*count, NULL, GL_STATIC_DRAW);

    // Transfer the vertex positions:
    glBufferSubData(GL_ARRAY_BUFFER, 0, 8*count, vertices_position);
    // Transfer the texture coordinates:
    glBufferSubData(GL_ARRAY_BUFFER, 8*count, 8*count, texture_coord);

    // Create an Element Array Buffer that will store the indices array:
    GLuint eab;
    glGenBuffers(1, &eab);

    // Transfer the data from indices to eab
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eab);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*count, indices, GL_STATIC_DRAW);

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
    glVertexAttribPointer(texture_coord_attribute, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(8*count));
    glEnableVertexAttribArray(texture_coord_attribute);
    return vao;
}

void add_quad(GLfloat vert[], GLuint ind[], GLfloat tex[], int i, double lx, double hx, double ly, double hy){
    vert[8*i+0] = vert[8*i+2] = lx;
    vert[8*i+4] = vert[8*i+6] = hx;
    vert[8*i+1] = vert[8*i+7] = ly;
    vert[8*i+3] = vert[8*i+5] = hy;

    ind[6*i+0] = ind[6*i+5] = 4*i+0;
    ind[6*i+2] = ind[6*i+3] = 4*i+2;
    ind[6*i+1] =              4*i+1;
    ind[6*i+4] =              4*i+3;

    tex[6*i+0] = tex[6*i+1] = tex[6*i+3] = tex[6*i+6] = 0.0;
    tex[6*i+2] = tex[6*i+4] = tex[6*i+5] = tex[6*i+7] = 1.0;
}

void renderer_init() {
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
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    shader = create_program("shaders/vert.shader", "shaders/frag.shader");
    amuletImage = load_image(AMULET, &w, &h);
    render_inited = true;

}

void render_bullet(Bullet bullet){
    //GLuint vao = initialize_quad(bullet.x, bullet.y);
    //glBindVertexArray(vao);
}

void render_bullets(std::list<Bullet> *bullets){
    if(!render_inited) return;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    int count = bullets->size();
    GLfloat vertices_position[count * 8];
    GLuint indices[count * 6];
    GLfloat texture_coord[count * 8];
    int i = 0;
    for (std::list<Bullet>::iterator b = bullets->begin(); b != bullets->end(); b++){
        double lx = XU*(b->x - w/2.0)-1.0, hx = XU*(b->x + w/2.0)-1.0;
        double ly = YU*(b->y - h/2.0)-1.0, hy = YU*(b->y + h/2.0)-1.0;
        add_quad(vertices_position, indices, texture_coord,  i, lx, hx, ly, hy);
        i++;
    }
    GLuint vao = initialize_quads(vertices_position, indices, texture_coord, count);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, count*6, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);
}

void renderer_close() {

    render_inited = false;
}
