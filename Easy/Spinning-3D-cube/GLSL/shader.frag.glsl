#version 330 core
out vec4 FragColor;
in vec3 vertexColour;
void main(){
    FragColor = vec4(vertexColour, 1.0);
}
