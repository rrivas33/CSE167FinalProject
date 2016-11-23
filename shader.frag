#version 330 core
// This is a sample fragment shader.

// Inputs to the fragment shader are the outputs of the same name from the vertex shader.
// Note that you do not have access to the vertex shader's default output, gl_Position.
in vec3 TexCoords;

// You can output many things. The first vec4 type output determines the color of the fragment
out vec4 color;

//Skybox
uniform samplerCube skybox;

void main()
{
    // Color everything a hot pink color. An alpha of 1.0f means it is not transparent.
    color = texture(skybox, TexCoords);
    //color = vec4(0.888f, 0.25f, 0.66f, 1.0f);
}
 
