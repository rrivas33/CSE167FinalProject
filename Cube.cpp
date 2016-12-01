#include "Cube.h"

Cube::Cube()
{
    toWorld = glm::mat4(1.0f);
    
    // Setup skybox VAO
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glBindVertexArray(0);
    
    // Cubemap (Skybox)
    std::vector<const GLchar*> faces;
    
    faces.push_back("/Users/CR7/Desktop/UCSD/FALL16/CSE167/CSE167FinalProject/CSE167FinalProject/sky2.jpg");
    faces.push_back("/Users/CR7/Desktop/UCSD/FALL16/CSE167/CSE167FinalProject/CSE167FinalProject/sky2.jpg");
    faces.push_back("/Users/CR7/Desktop/UCSD/FALL16/CSE167/CSE167FinalProject/CSE167FinalProject/sky2.jpg");
    faces.push_back("/Users/CR7/Desktop/UCSD/FALL16/CSE167/CSE167FinalProject/CSE167FinalProject/floor2.jpg");
    faces.push_back("/Users/CR7/Desktop/UCSD/FALL16/CSE167/CSE167FinalProject/CSE167FinalProject/sky2.jpg");
    faces.push_back("/Users/CR7/Desktop/UCSD/FALL16/CSE167/CSE167FinalProject/CSE167FinalProject/sky2.jpg");
    
    /*
     faces.push_back("/Users/CR7/Desktop/UCSD/FALL16/CSE167/CSE167FinalProject/CSE167FinalProject/right.tga");
     faces.push_back("/Users/CR7/Desktop/UCSD/FALL16/CSE167/CSE167FinalProject/CSE167FinalProject/left.tga");
     faces.push_back("/Users/CR7/Desktop/UCSD/FALL16/CSE167/CSE167FinalProject/CSE167FinalProject/top.tga");
     faces.push_back("/Users/CR7/Desktop/UCSD/FALL16/CSE167/CSE167FinalProject/CSE167FinalProject/base.tga");
     faces.push_back("/Users/CR7/Desktop/UCSD/FALL16/CSE167/CSE167FinalProject/CSE167FinalProject/front.tga");
     faces.push_back("/Users/CR7/Desktop/UCSD/FALL16/CSE167/CSE167FinalProject/CSE167FinalProject/back.tga");
     */
    
    cubemapTexture = loadCubemap(faces);
}

Cube::~Cube()
{ 
    // Delete previously generated buffers. Note that forgetting to do this can waste GPU memory in a
    // large project! This could crash the graphics driver due to memory leaks, or slow down application performance!
    glDeleteVertexArrays(1, &skyboxVAO);
    glDeleteBuffers(1, &skyboxVBO);
}

void Cube::Draw(GLuint shaderProgram)
{
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //std::cout << "Drawing cube \n"<<std::endl;
    // Draw skybox
    glDepthMask(GL_FALSE);// Remember to turn depth writing off
    
    // skybox cube
    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(shaderProgram, "skybox"), 0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthMask(GL_TRUE);
}

// Loads a cubemap texture from 6 individual texture faces
// Order should be:
// +X (right)
// -X (left)
// +Y (top)
// -Y (bottom)
// +Z (front)
// -Z (back)
GLuint Cube::loadCubemap(std::vector<const GLchar*> faces)
{
    GLuint textureID;
    glGenTextures(1, &textureID);

    
    int width,height;
    unsigned char* image;
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    for(GLuint i = 0; i < faces.size(); i++)
    {
        image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
    }
     
    // Use bilinear interpolation:
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    
    return textureID;
}
