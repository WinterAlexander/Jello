out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D tex;

void main()
{
    FragColor = vec4(color, 1.0) * texture(tex, texCoord);
}