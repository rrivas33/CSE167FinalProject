#include "Building.h"


Building::Building(int length, int width, int height, glm::vec3 location)
{
    model = glm::translate(glm::mat4(1.0f), location);
    createBuilding(length, width, height);
    
    glGenVertexArrays(1, &buildingVAO);
    glGenBuffers(1, &buildingVBO);
    glBindVertexArray(buildingVAO);
    glBindBuffer(GL_ARRAY_BUFFER, buildingVBO);
    glBufferData(GL_ARRAY_BUFFER, buildingVertices.size() * sizeof(glm::vec3), buildingVertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*) 0);
    glBindVertexArray(0);
    

    
    buildingTexture = loadTexture("/Users/Raul/Downloads/15_glass_building_skyscraper_texture-seamless.jpg");
} 

void Building::draw(GLuint shader)
{
    
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    std::cout << "Drawing Building \n"<<std::endl;
    // Draw skybox
    //glDepthMask(GL_FALSE);// Remember to turn depth writing off
    
    // skybox cube
    glBindVertexArray(buildingVAO);
    glActiveTexture(GL_TEXTURE0);
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &model[0][0]);
    glUniform1i(glGetUniformLocation(shader, "building"), 0);
    //std::cout << "buildingTexture: " << buildingTexture << std::endl;
    glBindTexture(GL_TEXTURE_2D, buildingTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    
    

    
}

GLuint Building::loadTexture(GLchar* path)
{
    //Generate texture ID and load texture data
    GLuint textureID;
    glGenTextures(1, &textureID);
    int width,height;
    unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
    // Assign texture to ID
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    // Parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);
    return textureID;
}

void Building::createBuilding(int length, int width, int height)
{
    
//    //front face
//    buildingVertices.push_back(glm::vec3(-5.0f, -5.0f, 5.0f));
//    buildingVertices.push_back(glm::vec3(-5.0f, 5.0f, 5.0f));
//    buildingVertices.push_back(glm::vec3(5.0f, 5.0f, 5.0f));
//    buildingVertices.push_back(glm::vec3(5.0f, 5.0f, 5.0f));
//    buildingVertices.push_back(glm::vec3(5.0f, -5.0f, 5.0f));
//    buildingVertices.push_back(glm::vec3(-5.0f, -5.0f, 5.0f));
//    
//    //back face
//    buildingVertices.push_back(glm::vec3(-5.0f, -5.0f, -5.0f));
//    buildingVertices.push_back(glm::vec3(5.0f, -5.0f, -5.0f));
//    buildingVertices.push_back(glm::vec3(-5.0f, 5.0f, -5.0f));
//    buildingVertices.push_back(glm::vec3(-5.0f, 5.0f, -5.0f));
//    buildingVertices.push_back(glm::vec3(5.0f, -5.0f, -5.0f));
//    buildingVertices.push_back(glm::vec3(5.0f, 5.0f, -5.0f));
//    
//    
//    
//    //left face
//    buildingVertices.push_back(glm::vec3(-5.0f, -5.0f, 5.0f));
//    buildingVertices.push_back(glm::vec3(-5.0f, -5.0f, -5.0f));
//    buildingVertices.push_back(glm::vec3(-5.0f, 5.0f, -5.0f));
//    buildingVertices.push_back(glm::vec3(-5.0f, 5.0f, -5.0f));
//    buildingVertices.push_back(glm::vec3(-5.0f, 5.0f, 5.0f));
//    buildingVertices.push_back(glm::vec3(-5.0f, -5.0f, 5.0f));
//    
//    //right face
//    buildingVertices.push_back(glm::vec3(5.0f, -5.0f, -5.0f));
//    buildingVertices.push_back(glm::vec3(5.0f, -5.0f, 5.0f));
//    buildingVertices.push_back(glm::vec3(5.0f, 5.0f, 5.0f));
//    buildingVertices.push_back(glm::vec3(5.0f, 5.0f, 5.0f));
//    buildingVertices.push_back(glm::vec3(5.0f, 5.0f, -5.0f));
//    buildingVertices.push_back(glm::vec3(5.0f, -5.0f, -5.0f));
//    
//    //top face
//    buildingVertices.push_back(glm::vec3(-5.0f, 5.0f, -5.0f));
//    buildingVertices.push_back(glm::vec3(5.0f, 5.0f, -5.0f));
//    buildingVertices.push_back(glm::vec3(5.0f, 5.0f, 5.0f));
//    buildingVertices.push_back(glm::vec3(5.0f, 5.0f, 5.0f));
//    buildingVertices.push_back(glm::vec3(-5.0f, 5.0f, 5.0f));
//    buildingVertices.push_back(glm::vec3(-5.0f, 5.0f, -5.0f));
//    
//    //bottom face
//    buildingVertices.push_back(glm::vec3(-5.0f, -5.0f, -5.0f));
//    buildingVertices.push_back(glm::vec3(-5.0f, -5.0f, 5.0f));
//    buildingVertices.push_back(glm::vec3(5.0f, -5.0f, -5.0f));
//    buildingVertices.push_back(glm::vec3(5.0f, -5.0f, -5.0f));
//    buildingVertices.push_back(glm::vec3(-5.0f, -5.0f, 5.0f));
//    buildingVertices.push_back(glm::vec3(5.0f, -5.0f, 5.0f));
    
    //front face
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(1.0f, -1.0f, 1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f));
    
    //back face
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(1.0f, -1.0f, -1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(1.0f, -1.0f, -1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(1.0f, 1.0f, -1.0f, 1.0f));
    
    
    
    //left face
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f));
    
    //right face
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(1.0f, -1.0f, -1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(1.0f, -1.0f, 1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(1.0f, 1.0f, -1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(1.0f, -1.0f, -1.0f, 1.0f));
    
    //top face
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(1.0f, 1.0f, -1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f));
    
    //bottom face
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(1.0f, -1.0f, -1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(1.0f, -1.0f, -1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f));
    buildingVertices.push_back(glm::scale(glm::mat4(1.0f), glm::vec3(length, width, height)) * glm::vec4(1.0f, -1.0f, 1.0f, 1.0f));
}

