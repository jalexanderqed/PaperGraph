#version 330 core

#define MAX_NUM_LIGHTS 4

#define LIGHT_DISABLED 0
#define LIGHT_POINT 1
#define LIGHT_DIRECTION 2

in vec3 vertexColor;
in vec3 vertexNormal;
in vec3 vertexPos;

out vec4 color;

struct Light{
    int type;
    vec3 color;
    vec3 position;
};

uniform Light lights[MAX_NUM_LIGHTS];
uniform vec3 viewPos;

vec3 CalcDirLight(Light light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main(){
    vec3 result = vec3(0, 0, 0);

    vec3 viewDir = normalize(viewPos - vertexPos);

    for(int i = 0; i < MAX_NUM_LIGHTS; i++){
        if(lights[i].type == LIGHT_DIRECTION){
            result += CalcDirLight(lights[i], vertexNormal, viewDir);
        }
        else if(lights[i].type == LIGHT_POINT){
            result += CalcPointLight(lights[i], vertexNormal, vertexPos, viewDir);
        }
    }

    color = vec4(result, 1.0f);
}

vec3 CalcDirLight(Light light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.position);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    float spec = 0;
    // Combine results
    vec3 ambient  = light.color * vertexColor;
    vec3 diffuse  = diff * light.color * vertexColor;
    vec3 specular = spec * light.color * vertexColor;
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    float spec = 0.0f;
    // Attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0f / (1.0f + 0.09f * distance +
        0.032 * (distance * distance));
    // Combine results
    vec3 ambient = light.color * vertexColor;
    vec3 diffuse  = diff * light.color * vertexColor;
    vec3 specular = spec * light.color * vertexColor;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}