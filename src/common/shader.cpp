#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include "../../include/common/shader.h"

#include <Python.h>

bool read_shader_file(const char *fname, std::vector<char> &buffer) {
    // std::cout << __FUNCTION__ << " " << fname << '\n';
    std::ifstream in;
    // std::cout << getwd(0) << std::endl;
    in.open(fname, std::ios::binary);

    if(in.is_open()) {
        // Get the number of bytes stored in this file
        in.seekg(0, std::ios::end);
        size_t length = (size_t)in.tellg();

        // Go to start of the file
        in.seekg(0, std::ios::beg);

        // Read the content of the file in a buffer
        buffer.resize(length + 1);
        in.read(&buffer[0], length);
        in.close();
        // Add a valid C - string end
        buffer[length] = '\0';
        return true;
    }
    else {
        // std::cerr << __FUNCTION__ << " failed\n";
        return false;
    }
}


void read_shader_src(const char *fname, std::vector<char> &buffer) {
    if (read_shader_file(fname, buffer)) {
        // ok
    }
    else {
        std::cerr << "Unable to open " << fname << " I'm out!" << std::endl;
        exit(-1);
    }
}

GLuint load_and_compile_shader(const char *fname, GLenum shaderType) {
    // Load a shader from an external file
    std::vector<char> buffer;
    read_shader_src(fname, buffer);
    const char *src = &buffer[0];

    // Compile the shader
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    return shader;
}

GLuint create_program(const char *path_vert_shader, const char *path_frag_shader) {
    // Load and compile the vertex and fragment shaders
    GLuint vertexShader = load_and_compile_shader(path_vert_shader, GL_VERTEX_SHADER);
    GLuint fragmentShader = load_and_compile_shader(path_frag_shader, GL_FRAGMENT_SHADER);

    // Attach the above shader to a program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // Flag the shaders for deletion
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Link and use the program
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    return shaderProgram;
}
