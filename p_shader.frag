#version 330 core

out vec4 FragColor;
uniform vec3 color;

in vec2 TexCoord;

uniform sampler2D outTexture;

void main(){
     FragColor = texture(ourTexture,TexCoord);
}