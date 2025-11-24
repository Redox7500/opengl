#version 410 core

in vec3 vFragmentPosition;
in vec3 vNormal;
in vec2 vUv;

out vec4 vFragmentColor;

uniform vec3 uViewPosition;
uniform vec3 uLightDirection;
uniform vec3 uLightColor;

uniform sampler2D uAlbedoMap;
uniform sampler2D uMetallicMap;
uniform sampler2D uRoughnessMap;
uniform sampler2D uAoMap;

const float PI = 3.14159265f;

float distributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.f);
    float NdotH2 = NdotH * NdotH;

    float denominator = (NdotH2 * (a2 - 1.f) + 1.f);
    denominator = PI * denominator * denominator;
    return a2 / denominator;
}

float geometrySchlickGGX(float NdotV, float roughness)
{
    float r = roughness + 1.f;
    float k = (r * r) / 8.f;
    return NdotV / (NdotV * (1.f - k) + k);
}

float geometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.f);
    float NdotL = max(dot(N, L), 0.f);
    float ggx2 = geometrySchlickGGX(NdotV, roughness);
    float ggx1 = geometrySchlickGGX(NdotL, roughness);
    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.f - F0) * pow(1.f - cosTheta, 5.f);
}

void main()
{
    vec4 albedoSample = texture(uAlbedoMap, vUv);
    vec3 albedo = pow(albedoSample.rgb, vec3(2.2f));
    // vec3 albedo = pow(vec3(1.f, 0.f, 0.f), vec3(2.2f));
    float albedoAlpha = albedoSample.a;
    // float albedoAlpha = 1.f;
    float metallic = texture(uMetallicMap, vUv).r;
    float roughness = texture(uRoughnessMap, vUv).r;
    float ao = texture(uAoMap, vUv).r;

    vec3 N = normalize(vNormal);
    vec3 V = normalize(uViewPosition - vFragmentPosition);
    vec3 L = normalize(-uLightDirection);
    vec3 H = normalize(V + L);

    vec3 F0 = vec3(0.04f);
    F0 = mix(F0, albedo, metallic);

    float NDF = distributionGGX(N, H, roughness);
    float G = geometrySmith(N, V, L, roughness);
    vec3 F = fresnelSchlick(max(dot(H, V), 0.f), F0);

    vec3 numerator = NDF * G * F;
    float denominator = 4.f * max(dot(N, V), 0.f) * max(dot(N, L), 0.f) + 0.001f;
    vec3 specular = numerator / denominator;

    vec3 kS = F;
    vec3 kD = (vec3(1.f) - kS) * (1.f - metallic);
    
    float NdotL = max(dot(N, L), 0.f);

    vec3 ambient = vec3(0.03f) * albedo * ao;
    vec3 diffuse = kD * albedo / PI;
    vec3 radiance = uLightColor;

    vec3 Lo = (diffuse + specular) * radiance * NdotL;

    vec3 color = ambient + Lo;
    color = color / (color + vec3(1.f));
    color = pow(color, vec3(1.f / 2.2f));

    vFragmentColor = vec4(color, albedoAlpha);
    // vFragmentColor = vec4(0.2f, 0.2f, 1.f, 1.f);
    // vFragmentColor = vec4(vUv, 0.f, 1.f);
    // vFragmentColor = texture(uAlbedoMap, vUv);
}