#version 400 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vData
{
    vec3 normal;
} vertex;

uniform mat4 model;

void main()
{
    gl_Position = model * vec4(aPos, 1.0f);
    vertex.normal = normalize(mat3(transpose(inverse(model))) * aNormal);
}