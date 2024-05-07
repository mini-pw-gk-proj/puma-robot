#version 400 core
layout (points) in;
layout (line_strip, max_vertices = 2) out;

in vec3 prevPos[];
in vec3 currPos[];
in vec3 tangent[];
in float ttl[];

uniform mat4 projection;
uniform mat4 view;
uniform vec3 viewPos;

void main() {
    gl_Position = projection * view * vec4(prevPos[0], 1);
    EmitVertex();
    gl_Position = projection * view * vec4(currPos[0], 1);
    EmitVertex();
    EndPrimitive();
}