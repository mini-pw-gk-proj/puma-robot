#version 400 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

in vec3 prevPos[];
in vec3 currPos[];
in vec3 tangent[];
in float ttl[];

out vec2 texCoords;
out float alpha;

uniform mat4 projection;
uniform mat4 view;
uniform vec3 viewPos;
uniform float maxTTL;

void main() {
    vec3 toCamera = normalize(currPos[0] - viewPos);
    vec3 dir = tangent[0];
    vec3 normal = normalize(cross(toCamera, dir));
    float width = 0.01 * length(dir);
    float length = 0.05;

    alpha = (ttl[0])/maxTTL;
    gl_Position = projection * view * vec4(prevPos[0] + width * normal, 1);
    texCoords = vec2(0,0);
    EmitVertex();
    gl_Position = projection * view * vec4(currPos[0] + length * dir + width * normal, 1);
    texCoords = vec2(0,1);
    EmitVertex();
    gl_Position = projection * view * vec4(prevPos[0] - width * normal, 1);
    texCoords = vec2(1,0);
    EmitVertex();
    gl_Position = projection * view * vec4(currPos[0] + length * dir - width*normal, 1);
    texCoords = vec2(1,1);
    EmitVertex();
    EndPrimitive();
}