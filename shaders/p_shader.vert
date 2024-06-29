#version 330 core

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

layout (location=0) in vec3 pos;
layout (location =1) in vec3 aNormal;
layout (location =2) in vec2 texCoord;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main(){
     TexCoord = texCoord;
    Normal = mat3(transpose(inverse(model))) * aNormal;  
     FragPos = vec3(model*vec4(pos,1.0f));
     gl_Position = proj*view* vec4(FragPos,1.0f);
}