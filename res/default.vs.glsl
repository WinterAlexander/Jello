in vec3 aPos;   // the position variable has attribute position 0
in vec3 aColor; // the color variable has attribute position 1

out vec3 color; // output a color to the fragment shader

uniform vec2 offset;

void main()
{
    gl_Position = vec4(aPos + vec3(offset, 0.0), 1.0);
    color = aColor; // set ourColor to the input color we got from the vertex data
}