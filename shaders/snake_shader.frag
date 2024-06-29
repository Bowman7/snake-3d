#version 330 core

in vec3 aColor;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;


uniform vec3 ObjectColor;
uniform vec3 LightColor;
uniform vec3 LightPos;
uniform vec3 ViewPos;

void main(){
     //diffuse light
     vec3 norm = normalize(Normal);
     vec3 lightDir = normalize(LightPos - FragPos);
     float diff =max(dot(norm,lightDir),0.0);
     vec3 diffuse = diff * LightColor;

     //specular
     float specularStrength = 0.9;
     vec3 viewDir = normalize(ViewPos - FragPos);
     vec3 reflectDir = reflect(-lightDir,norm);
     float spec = pow(max(dot(viewDir,reflectDir),0.0),32);
     vec3 specular = specularStrength*spec*LightColor;
     
     float ambientStrength = 0.4;
     vec3 ambient = ambientStrength * LightColor;

     vec3 result = (ambient+diffuse + specular) * ObjectColor;
     FragColor = vec4(result,1.0);
}