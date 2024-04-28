#version 400 core
layout (triangles_adjacency) in;
layout (triangle_strip, max_vertices = 15) out;

in vData {
    vec3 normal;
} vertex[];

uniform mat4 projection;
uniform mat4 view;

uniform vec3 lightPos;

bool isTriangleFacingLight(vec3 light, int i1, int i2, int i3);
void emitVertex(int i, bool isFacing);
void emitWall(int i1, int i3);

void main()
{
    bool isFacing = isTriangleFacingLight(lightPos, 0, 1, 2);
    for(int i = 0; i< 3; i++) {
        emitVertex(i, isFacing);
    }
    EndPrimitive();

    if(isFacing) {
        if(!isTriangleFacingLight(lightPos, 0, 3, 1))
            emitWall(0, 1);
        if(!isTriangleFacingLight(lightPos, 1, 4, 2))
            emitWall(1, 2);
        if(!isTriangleFacingLight(lightPos, 2, 5, 0))
            emitWall(2, 0);
    }

}

void emitVertex(int i, bool extrude) {
    vec3 vector = normalize(vec3(gl_in[i].gl_Position) - lightPos);
    vec4 offset = !extrude ? vec4(vector*20, 0) : vec4(0);
    vec4 position = gl_in[i].gl_Position + offset;
    gl_Position = projection * view * position;
    EmitVertex();
}

void emitWall(int i1, int i3) {
    vec3 v1 = vec3(gl_in[i1].gl_Position);
    vec3 v3 = vec3(gl_in[i3].gl_Position);

    emitVertex(i3, true);
    emitVertex(i1, true);
    emitVertex(i3, false);
    emitVertex(i1, false);

    EndPrimitive();
}

bool isTriangleFacingLight(vec3 light, int i1, int i2, int i3) {
    vec3 v1 = vec3(gl_in[i1].gl_Position);
    vec3 v2 = vec3(gl_in[i2].gl_Position);
    vec3 v3 = vec3(gl_in[i3].gl_Position);
    vec3 c = cross(v2 - v1, v3 - v1);
    return dot(light - v1, c) >= 0;
}