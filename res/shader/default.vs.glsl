layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1
layout (location = 2) in vec2 aTexCoord;

out vec3 color; // output a color to the fragment shader
out vec2 texCoord;

uniform vec2 offset;

void main()
{
    gl_Position = vec4(aPos + vec3(offset, 0.0), 1.0);
    color = aColor; // set ourColor to the input color we got from the vertex data
    texCoord = aTexCoord;
}