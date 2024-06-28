#version 330 core

in vec2 TexCoords;
out vec4 colors;

uniform sampler2D text;
uniform vec3 textColor;

void main(){
     vec4 sampled =vec4(1.0f,1.0f,1.0f,texture(text,TexCoords).r);
     colors = vec4(textColor,1.0f)*sampled;
}