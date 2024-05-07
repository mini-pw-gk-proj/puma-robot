#version 400 core
#define TRAIL_POINTS 256
layout (points) in;
layout (line_strip, max_vertices = TRAIL_POINTS) out;

uniform mat4 view;
uniform mat4 projection;

uniform vec3 trailPoints[TRAIL_POINTS];
uniform int pointCount;
uniform int caret;
uniform float startingOpacity;

out float opacity;

void main() {
    int cur = caret == 0? TRAIL_POINTS-1 : caret - 1;
    for(int i=0; i<pointCount; i++)
    {
        opacity = startingOpacity * (1 - float(i) / TRAIL_POINTS);
        gl_Position = projection * view * vec4(trailPoints[cur], 1);
        EmitVertex();

        cur--;
        if(cur < 0) cur = TRAIL_POINTS - 1;
    }
    EndPrimitive();
}