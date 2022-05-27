#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1
uniform mat4 transform; // the matrix uniform
out vec3 vertexColour;
void main(){
    gl_Position = transform * vec4(aPos, 1.0);
    vertexColour = aColor;
}
