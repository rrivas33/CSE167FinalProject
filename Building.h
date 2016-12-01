//
//  Building.h
//  CSE167FinalProject
//
//  Created by raul rivas on 11/23/16.
//  Copyright © 2016 raul rivas. All rights reserved.
//

#ifndef Building_h
#define Building_h
 

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

class Building {
    
public:
    GLuint buildingVAO, buildingVBO;
    glm::mat4 model; // model matrix
    std::vector<glm::vec3> buildingVertices;
    GLuint buildingTexture;
    
    Building(int length, int width, int height, glm::vec3 location);
    void draw(GLuint shaderProgram);
    void createBuilding(int length, int width, int height);
    GLuint loadTexture(GLchar* path);
    
    //~Building();
};


#endif /* Building_h */
