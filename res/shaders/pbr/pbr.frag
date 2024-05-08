#version 330 core
out vec4 fragColor;

in vec3 fragPos;
in vec3 normal;
in vec2 texCoords;

uniform vec3 viewPos;
uniform bool isMirror;

// Material
struct Material {
    bool hasTexture;
    sampler2D texture;

    vec4 albedo;
    float metallic;
    float roughness;
};
uniform Material material;

// Point Light
struct PointLight {
    vec3 position;
    vec3 color;
    float strength;
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
};
uniform PointLight pointLight;
uniform vec3 ambient;

const float PI = 3.14159265359;

vec3 fresnelSchlick(float cosTheta, vec3 F0) {
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness) {
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float num = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness) {
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return num / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

void main() {
    vec4 albedo = material.hasTexture ? texture(material.texture, texCoords) : material.albedo;
    float metallic  = material.metallic;
    float roughness =  material.roughness;

    vec3 N = normalize(normal);
    vec3 V = normalize(viewPos - fragPos);

    vec3 Lo = vec3(0.0);
    float alpha = albedo.a;
    vec3 L = normalize(pointLight.position - fragPos);
    vec3 H = normalize(V + L);
    vec3 radiance = pointLight.color;
    // Fresnel
    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo.rgb, metallic);
    vec3 F  = fresnelSchlick(max(dot(H, V), 0.0), F0);

    float NDF = DistributionGGX(N, H, roughness);
    float G   = GeometrySmith(N, V, L, roughness);

    vec3 numerator    = NDF * G * F;
    float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0)  + 0.0001;
    vec3 specular     = numerator / denominator;

    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic;

    float NdotL = max(dot(N, L), 0.0);

    float lightCount = 2.f;
    Lo += (kD * albedo.rgb / PI + specular) * radiance * NdotL * pointLight.strength / lightCount;

    vec3 ambient = ambient * albedo.rgb;
    vec3 color   = ambient + Lo;
    if(isMirror && alpha==0) {
        alpha = specular.r;
        color = specular;
    }
    float gamma = 2.2f;
    color =  pow(color, vec3(1.0/gamma));
    fragColor = vec4(color, alpha);
}
