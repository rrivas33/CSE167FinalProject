//
//  BezierPatch.cpp
//  CSE167FinalProject
//
//  Created by Charlie Alexander Ponce on 11/24/16.
//  Copyright © 2016 Charlieexclusive. All rights reserved.
//

#include "BezierPatch.hpp"

BezierPatch::BezierPatch(){
    
    //toWorld = glm::mat4(1.0f);
    
    // Setup sphere VAO
    glGenVertexArrays(1, &curveVAO);
    glGenBuffers(1, &curveVBO);
    //glGenBuffers(1, &sphereNBO);
    glBindVertexArray(curveVAO);
    glBindBuffer(GL_ARRAY_BUFFER, curveVBO);
    glBufferData(GL_ARRAY_BUFFER, 0, 0, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    
    // Unbind the currently bound buffer so that we don't accidentally make unwanted changes to it.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // Unbind the VAO now so we don't accidentally tamper with it.
    // NOTE: You must NEVER unbind the element array buffer associated with a VAO!
    glBindVertexArray(0);
    
}

//This function calculates the coefficients of the bicubic equation
glm::mat4x4 BezierPatch::BicubicCoefficient(glm::mat4x4 G){
    glm::mat4x4 B(glm::vec4(-1,3,-3,1), glm::vec4(3,-6,3,0), glm::vec4(-3,3,0,0), glm::vec4(1,0,0,0));
    glm::mat4x4 C = B*G*B;
    return C;
}

//This function will evaluate the point x(u,v) on the Bezier Patch
glm::vec3 BezierPatch::PatchLocation(float u, float v){
    glm::vec4 U(u*u*u,u*u,u,1.0f);
    glm::vec4 V(v*v*v,v*v,v,1.0f);
    
    glm::vec4 X = Cx*U;
    float x_x = V.x*X.x + V.y*X.y + V.z*X.z + V.w*X.w;
    glm::vec4 Y = Cy*U;
    float x_y = V.x*Y.x + V.y*Y.y + V.z*Y.z + V.w*Y.w;
    glm::vec4 Z = Cz*U;
    float x_z = V.x*Z.x + V.y*Z.y + V.z*Z. z+ V.w*Z.w;
    
    glm::vec3 x(x_x, x_y, x_z);
    return x;
}

//This function Calculates a Curve Based on Control Points
void BezierPatch::solidBezierPatch(){
    //curveVertices.clear();
    //std::cout<<"HERE" <<std::endl;
    if(start){
        glm::vec3 X;
        float u = 0.0;
        float v = 0.0;
        int count = 0;
        
//        srand (time(NULL));
//        random = (rand() % 100+1)/1000.0;
//        std::cout<< "first RANDOM: " << random << std::endl;
//        if (random < 0.009){
//            random += 0.01112;
//        }
//        else if (random > 0.05){
//            random -= 0.03;
//        }
//        std::cout<< "then RANDOM: " << random << std::endl;
        
        srand (time(NULL));
        p3.z += -(rand() % 250 + 100);
        p2.z += -(rand() % 250 + 100);
        p1.z += -(rand() % 250 + 100);
        p0.z += -(rand() % 250 + 100);
        
        /*
        p6.z += -(rand() % 15 + 30);
        p5.z += -(rand() % 5 + 20);
        
        p9.z += -(rand() % 10 + 10);
        p10.z += -(rand() % 5 + 10);
        
         */
        
        p0.x += -(rand() % 250 + 100);
        p4.x += -(rand() % 250 + 100);
        p8.x += -(rand() % 250 + 100);
        p12.x += -(rand() % 250 + 100);

        p12.z += (rand() % 250 + 100);
        p13.z += (rand() % 250 + 100);
        p14.z += (rand() % 250 + 100);
        p15.z += (rand() % 250 + 100);

        p3.x += (rand() % 250 + 100);
        p7.x += (rand() % 250 + 100);
        p11.x += (rand() % 250 + 100);
        p15.x += (rand() % 250 + 100);
        
        update();
        
        while(u<=1.0){
            while(v<=1.0)
            {
                //std::cout<<"u: " << u << " v: " << v << std::endl;
                X = PatchLocation(u, v);
                //std::cout<<"x: " << X.x << " y: " << X.y << " z: " << X.z <<std::endl;
                curveVertices.push_back(X);
                if((u==1 && v==1)){
                    break;
                }//end if
//                if(count==1){
//                    count--;
//                    //u-=random;
//                    //v+=random;
//                    u-=0.015625;
//                    X = PatchLocation(u, v);
//                    curveVertices.push_back(X);
//                    v+=0.015625;
//                    X = PatchLocation(u, v);
//                    curveVertices.push_back(X);
//                }else{
//                    count++;
//                    u+=0.015625;
//                    //u+=random;
//                }//end else
                v+=0.015625;
            }//end while
            v=0.0;
            //u+=random;
            u+=0.015625;
        }//end while
        
        start =false;
    }//end if
    
    glBindVertexArray(curveVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, curveVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * curveVertices.size(), &curveVertices[0], GL_STATIC_DRAW);
    
    // Unbind the currently bound buffer so that we don't accidentally make unwanted changes to it.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // Unbind the VAO now so we don't accidentally tamper with it.
    // NOTE: You must NEVER unbind the element array buffer associated with a VAO!
    glBindVertexArray(0);
    
    glBindVertexArray(curveVAO);
    
    glPointSize(2.0f);
    glDrawArrays(GL_POINTS, 0, curveVertices.size());
    
    glBindVertexArray(0);
    
}

void BezierPatch::Draw(GLuint shaderProgram)
{
    //std::cout<< "Drawing Patch \n";
    solidBezierPatch();
}

void BezierPatch::update()
{
    Gx = glm::mat4x4(glm::vec4(p0.x, p4.x, p8.x, p12.x), glm::vec4(p1.x, p5.x, p9.x, p13.x), glm::vec4(p2.x, p6.x, p10.x, p14.x), glm::vec4(p3.x, p7.x, p11.x, p15.x));
    
    Gy = glm::mat4x4(glm::vec4(p0.y, p4.y, p8.y, p12.y), glm::vec4(p1.y, p5.y, p9.y, p13.y), glm::vec4(p2.y, p6.y, p10.y, p14.y), glm::vec4(p3.y, p7.y, p11.y, p15.y));
    
    Gz = glm::mat4x4(glm::vec4(p0.z, p4.z, p8.z, p12.z), glm::vec4(p1.z, p5.z, p9.z, p13.z), glm::vec4(p2.z, p6.z, p10.z, p14.z), glm::vec4(p3.z, p7.z, p11.z, p15.z));
    
    Cx = BicubicCoefficient(Gx);
    Cy = BicubicCoefficient(Gy); 
    Cz = BicubicCoefficient(Gz);
}


BezierPatch::~BezierPatch(){
    // Delete previously generated buffers. Note that forgetting to do this can waste GPU memory in a
    // large project! This could crash the graphics driver due to memory leaks, or slow down application performance!
    
    glDeleteVertexArrays(1, &curveVAO);
    glDeleteBuffers(1, &curveVBO);
}


