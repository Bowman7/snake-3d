#version 330 core

layout (location =0) in vec3 pos;
layout (location=1) in vec3 aNormal;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;

out vec3 Normal;
out vec3 FragPos;
void main(){
     gl_Position = proj*view*model*vec4(pos,1.0);
     FragPos = vec3(model*vec4(pos,1.0));		
     Normal = mat3(transpose(inverse(model)))*aNormal;
    
}