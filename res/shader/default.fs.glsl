out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 worldPosition; // position in world
in vec3 normal; 

uniform sampler2D u_texture;

uniform vec3 u_lightPositions[128];
uniform vec3 u_lightColors[128];
uniform int u_lightCount;

void main()
{
    vec3 norm = normalize(normal);
    
    vec3 light = 0.1 * vec3(1.0); // ambient lighting
    
    for(int i = 0; i < 128 && i < u_lightCount; i++) {
        vec3 lightDir = normalize(lightPositions[i] - worldPosition);
        vec3 lightColor = u_lightColors[i];
        
        light += max(dot(norm, lightDir), 0.0) * lightColor;
    } 

    FragColor = vec4(light * color, 1.0) * texture(tex, texCoord);
}