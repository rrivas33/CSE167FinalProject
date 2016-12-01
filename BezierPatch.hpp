//
//  BezierPatch.hpp
//  CSE167FinalProject
//
//  Created by Charlie Alexander Ponce on 11/24/16.
//  Copyright © 2016 Charlieexclusive. All rights reserved.
//

#ifndef BezierPatch_hpp
#define BezierPatch_hpp

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
#include <stdio.h>
#include <iostream>


class BezierPatch
{
public:
    bool start = true;
    float random;
    glm::vec3 WhereYouAt;
    
    //CONTROLPOINTS//
    glm::vec3 p0 = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 p1 = glm::vec3(10.0f, 0.0f, 0.0f);
    glm::vec3 p2 = glm::vec3(20.0f, 0.0f, 0.0f);
    glm::vec3 p3 = glm::vec3(30.0f, 0.0f, 0.0f);
    
    glm::vec3 p4 = glm::vec3(0.0f, 0.0f, 10.0f);
    glm::vec3 p5 = glm::vec3(10.0f, 0.0f, 10.0f);
    glm::vec3 p6 = glm::vec3(20.0f, 0.0f, 10.0f);
    glm::vec3 p7 = glm::vec3(30.0f, 0.0f, 10.0f);
    
    glm::vec3 p8 = glm::vec3(0.0f, 0.0f, 20.0f);
    glm::vec3 p9 = glm::vec3(10.0f, 0.0f, 20.0f);
    glm::vec3 p10 = glm::vec3(20.0f, 0.0f, 20.0f);
    glm::vec3 p11 = glm::vec3(30.0f, 0.0f, 20.0f);
    
    glm::vec3 p12 = glm::vec3(0.0f, 0.0f, 30.0f);
    glm::vec3 p13 = glm::vec3(10.0f, 0.0f, 30.0f);
    glm::vec3 p14 = glm::vec3(20.0f, 0.0f, 30.0f);
    glm::vec3 p15 = glm::vec3(30.0f, 0.0f, 30.0f);
    
    glm::mat4x4 Cx;
    glm::mat4x4 Cy;
    glm::mat4x4 Cz;
    
    glm::mat4x4 Gx;
    glm::mat4x4 Gy;
    glm::mat4x4 Gz;
    
    std::vector<glm::vec3> curveVertices;
    std::vector<glm::vec3> curveVerticesCopy;
    GLuint curveVAO, curveVBO; 
    
    BezierPatch();
    ~BezierPatch();
    void solidBezierPatch();
    void Draw(GLuint shaderProgram);
    void update();
    glm::mat4x4 BicubicCoefficient(glm::mat4x4 G);
    glm::vec3 PatchLocation(float u, float v);
    
};

#endif /* BezierPatch_hpp */
