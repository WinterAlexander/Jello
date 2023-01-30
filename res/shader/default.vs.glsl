layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;
layout (location = 4) in vec3 aTangent;

out vec3 color; // output a color to the fragment shader
out vec2 texCoord;
out vec3 worldPosition;
out mat3 tbn;

uniform mat4 u_transform;
uniform mat4 u_model;

void main()
{
    gl_Position = u_transform * vec4(aPos, 1.0);
    color = aColor; // set ourColor to the input color we got from the vertex data
    texCoord = aTexCoord;
    worldPosition = vec3(u_model * vec4(aPos, 1.0));

    vec3 normal = mat3(transpose(inverse(u_model))) * aNormal;
    vec3 tangent = mat3(transpose(inverse(u_model))) * aTangent;
    vec3 bitangent = cross(normal, tangent);

    tbn = mat3(tangent, bitangent, normal);
}