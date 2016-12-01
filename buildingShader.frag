#version 330 core
// This is a sample fragment shader.

// Inputs to the fragment shader are the outputs of the same name from the vertex shader.
// Note that you do not have access to the vertex shader's default output, gl_Position.
//in vec3 TexCoords;

// You can output many things. The first vec4 type output determines the color of the fragment
out vec4 color;

//Building
uniform samplerCube building;
 
void main()
{
    // Color everything a hot pink color. An alpha of 1.0f means it is not transparent.
    //color = texture(building, TexCoords);
    color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
//    if(building == 1)
//        color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
//    else
//        color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

