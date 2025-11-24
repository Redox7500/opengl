#version 410 core

in vec3 vFragmentPosition;
in vec3 vNormal;

out vec4 vFragmentColor;

uniform vec3 uViewPosition;
uniform vec3 uLightPosition;
uniform vec4 uObjectColor;
uniform vec4 uLightColor;
// with texture
// uniforms sampler2D uTexture;

void main()
{
    float ambientStrength = 0.1f;
    float diffuseStrength = 1.0f;
    float specularStrength = 0.0f;
    int specularShininess = 32;

    vec4 ambient = ambientStrength * uLightColor;

    vec3 lightDirection = normalize(uLightPosition - vFragmentPosition);
    float difference = max(dot(vNormal, lightDirection), 0.f);
    vec4 diffuse = diffuseStrength * difference * uLightColor;

    vec3 viewDirection = normalize(uViewPosition - vFragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, vNormal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.f), specularShininess);
    vec4 specular = specularStrength * spec * uLightColor;

    // with texture
    // vFragmentColor = (ambient + diffuse + specular) * texture(uTexture, vTextureCoordinate);

    vFragmentColor = (ambient + diffuse + specular) * uObjectColor;
}