#version 400 core
out vec4 fragColor;

in float opacity;

void main()
{
    fragColor = vec4(vec3(1.0f, 0.6f, 0.6f), opacity);
}
