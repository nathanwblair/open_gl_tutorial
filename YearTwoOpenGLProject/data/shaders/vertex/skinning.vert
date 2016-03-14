#version 330

layout(location=0) in vec4 position;
layout(location=2) in vec4 normal;
layout(location=3) in vec4 tangent;
layout(location=5) in vec4 indicies;
layout(location=6) in vec4 weights;
layout(location=7) in vec2 texCoord1;

out vec3 vPosition;
out vec2 vTexCoord;
out vec3 vNormal;
out vec3 vTangent;
out vec3 vBiTangent;

uniform mat4 modelTransform;
uniform mat4 projectionViewTransform;

const int MAX_BONES = 128;
uniform mat4 bones[MAX_BONES];

void main()
{
    vPosition = position.xyz;
    vNormal = normal.xyz;
    vTangent = tangent.xyz;
    vBiTangent = cross( normal.xyz, tangent.xyz );
    vTexCoord = texCoord1;

    ivec4 index = ivec4(indicies);

    vec4 P =  bones[index.x] * position * weights.x;
         P += bones[index.y] * position * weights.y;
         P += bones[index.z] * position * weights.z;
         P += bones[index.w] * position * weights.w;

    gl_Position = projectionViewTransform * modelTransform * P;
}
