#version 400 core
out vec4 FragColor;

in float alpha;
in vec2 texCoords;

struct Material {
    sampler2D texture;
};
uniform Material material;

void main()
{
    vec4 albedo = texture(material.texture, texCoords);
    FragColor = vec4(1,0.8,0.8/*albedo.rgb*/, 1.5*albedo.a * alpha*alpha);
}