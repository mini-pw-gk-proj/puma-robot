#version 400 core
layout (location = 0) in vec3 aPrevPos;
layout (location = 1) in vec3 aCurrPos;
layout (location = 2) in vec3 aTangent;
layout (location = 3) in float aTTL;

out vec3 prevPos;
out vec3 currPos;
out vec3 tangent;
out float ttl;

void main()
{
    prevPos = aPrevPos;
    currPos = aCurrPos;
    tangent = aTangent;
    ttl = aTTL;
}