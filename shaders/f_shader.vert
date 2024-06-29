#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 aNormal;


uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 Normal;
out vec3 FragPos;

void main(){
     Normal = mat3(transpose(inverse(model))) * aNormal; 
     FragPos = vec3(model*vec4(pos,1.0f));
     gl_Position =proj*view*vec4(FragPos,1.0f);
}