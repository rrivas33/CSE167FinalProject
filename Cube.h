#ifndef _CUBE_H_
#define _CUBE_H_

#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include "GLFW/glfw3.h"
// Use of degrees is deprecated. Use radians instead.
#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "vector"
#include "SOIL.h"
using namespace std;
#include <iostream>


 
class Cube
{
public:
    Cube();
    ~Cube();
    
    glm::mat4 toWorld;
    
    void Draw(GLuint shaderProgram);
    GLuint loadCubemap(std::vector<const GLchar*> faces);
    
    // These variables are needed for the shader program
    // Setup cube VAO
    GLuint skyboxVAO, skyboxVBO;
    GLuint cubemapTexture;
};

const GLfloat skyboxVertices[] = {
    // Positions
    -400.0f,  400.0f, -400.0f,
    -400.0f, -400.0f, -400.0f,
    400.0f, -400.0f, -400.0f,
    400.0f, -400.0f, -400.0f,
    400.0f,  400.0f, -400.0f,
    -400.0f,  400.0f, -400.0f,
    
    -400.0f, -400.0f,  400.0f,
    -400.0f, -400.0f, -400.0f,
    -400.0f,  400.0f, -400.0f,
    -400.0f,  400.0f, -400.0f,
    -400.0f,  400.0f,  400.0f,
    -400.0f, -400.0f,  400.0f,
    
    400.0f, -400.0f, -400.0f,
    400.0f, -400.0f,  400.0f,
    400.0f,  400.0f,  400.0f,
    400.0f,  400.0f,  400.0f,
    400.0f,  400.0f, -400.0f,
    400.0f, -400.0f, -400.0f,
    
    -400.0f, -400.0f,  400.0f,
    -400.0f,  400.0f,  400.0f,
    400.0f,  400.0f,  400.0f,
    400.0f,  400.0f,  400.0f,
    400.0f, -400.0f,  400.0f,
    -400.0f, -400.0f,  400.0f,
    
    -400.0f,  400.0f, -400.0f,
    400.0f,  400.0f, -400.0f,
    400.0f,  400.0f,  400.0f,
    400.0f,  400.0f,  400.0f,
    -400.0f,  400.0f,  400.0f,
    -400.0f,  400.0f, -400.0f,
    
    -400.0f, -400.0f, -400.0f,
    -400.0f, -400.0f,  400.0f,
    400.0f, -400.0f, -400.0f,
    400.0f, -400.0f, -400.0f,
    -400.0f, -400.0f,  400.0f,
    400.0f, -400.0f,  400.0f
};

#endif

