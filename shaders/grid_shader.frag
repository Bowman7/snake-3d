#version 330

out vec4 outColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec3 color;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;

void main() {
     //ambient
     float ambientStrength = 0.4f;
     vec3 ambient = ambientStrength *lightColor;

     //diffuse
     vec3 norm = normalize(Normal);
     vec3 lightDir = normalize(lightPos-FragPos);

     float diff = max(dot(norm,lightDir),0.0f);
     vec3 diffuse = diff *lightColor;

     //specular
     float specularStrength = 0.5f;
     vec3 viewDir = normalize(viewPos-FragPos);
     vec3 reflectDir = reflect(-lightDir,norm);

     float spec = pow(max(dot(viewDir,reflectDir),0.0f),64);
     vec3 specular = specularStrength*spec*lightColor;

     vec3 result = (ambient+diffuse+specular)*color;
     outColor = vec4(result,1.0f);
}