#version 400 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 col;

void main()
{
    col = vec3(gl_VertexID == 1, gl_VertexID == 2, gl_VertexID == 0);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}