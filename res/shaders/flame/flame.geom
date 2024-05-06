#version 400 core
layout (triangles_adjacency) in;
layout (triangle_strip, max_vertices = 15) out;

in vData {
    vec3 normal;
} vertex[];

out vec2 texCoord;
flat out float flame;

uniform mat4 projection;
uniform mat4 view;
uniform vec3 viewPos;
uniform float time;

bool isTriangleFacingDown(int i1, int i2, int i3);
void emitVertex(int i, bool isFacing, int adj);
void emitWall(int i1, int i3, int adj);

void main()
{
    bool isFacing = isTriangleFacingDown(0, 1, 2);
    if(isFacing) {
        for(int i = 0; i< 3; i++) {
            texCoord = vec2(1);
            flame = 0.0f;
            emitVertex(i, true, i);
        }
        EndPrimitive();
    }
    if(isFacing) {
        if(!isTriangleFacingDown(0, 3, 1))
        emitWall(0, 1, 3);
        if(!isTriangleFacingDown(1, 4, 2))
        emitWall(1, 2, 4);
        if(!isTriangleFacingDown(2, 5, 0))
        emitWall(2, 0, 5);
    }

}

void emitVertex(int i, bool extrude, int adj) {
    vec3 up = vec3(0,1,0);
    vec3 vector = normalize(up);
    vec4 offset = !extrude ? vec4(vector*0.4 + vec3(0.02*sin(5.23*time) + 0.03*cos(10.23*time) + 0.015*sin(34.2*time),0, 0.02*cos(15.01*time)) + 0.03*sin(7.34*time)+ 0.013*sin(27.2*time), 0) : vec4(0);
    float distanceToCamera = length(view * (vec4(viewPos,1) - (gl_in[i].gl_Position + offset)));
    offset += vec4(vertex[i].normal*0.0002*pow(distanceToCamera,1.5), 0);
    vec4 position = gl_in[i].gl_Position + offset;
    gl_Position = projection * view * position;
    EmitVertex();
}

void emitWall(int i1, int i3, int adj) {
    vec3 v1 = vec3(gl_in[i1].gl_Position);
    vec3 v3 = vec3(gl_in[i3].gl_Position);

    flame = 1.0f;
    texCoord = vec2(0,1);
    emitVertex(i3, true, adj);
    texCoord = vec2(1,1);
    emitVertex(i1, true, adj);
    texCoord = vec2(0,0);
    emitVertex(i3, false, adj);
    texCoord = vec2(1,0);
    emitVertex(i1, false, adj);

    EndPrimitive();
}

bool isTriangleFacingDown(int i1, int i2, int i3) {
//    if(abs(vertex[0].normal.y) < 0.01 || abs(vertex[1].normal.y) < 0.01 || abs(vertex[2].normal.y) < 0.01) return false;
    vec3 down = vec3(0,-1,0);
    vec3 v1 = vec3(gl_in[i1].gl_Position);
    vec3 v2 = vec3(gl_in[i2].gl_Position);
    vec3 v3 = vec3(gl_in[i3].gl_Position);
    vec3 c = cross(v2 - v1, v3 - v1);
    return dot(down, c) > -0.001;
}