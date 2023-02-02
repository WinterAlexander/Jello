out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 worldPosition; // position in world
in mat3 tbn;

uniform sampler2D u_texture;
uniform sampler2D u_normal;

uniform vec3 u_lightPositions[128];
uniform vec3 u_lightColors[128];
uniform int u_lightCount;
uniform vec3 u_viewPosition;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  
uniform Material u_material;

void main()
{
    vec3 norm = normalize(tbn * (texture(u_normal, texCoord).rgb * 2.0 - vec3(1.0)));

    vec3 light = 0.4 * u_material.ambient * vec3(1.0); // ambient lighting
    
    for(int i = 0; i < 128 && i < u_lightCount; i++) {
        vec3 lightDir = normalize(u_lightPositions[i] - worldPosition);
        vec3 lightColor = u_lightColors[i];

        light += max(dot(norm, lightDir), 0.0) * lightColor * u_material.diffuse;

        vec3 viewDir = normalize(u_viewPosition - worldPosition);
        vec3 reflectDir = reflect(-lightDir, norm);

        float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
        light += u_material.specular * spec * lightColor;
    }

    FragColor = vec4(light * color, 1.0) * texture(u_texture, texCoord);
}