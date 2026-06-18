#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

uniform mat4 model;
uniform mat4 projection;
uniform vec2 uvOffset;
uniform vec2 frameSize;
uniform vec2 textureSize;

out vec2 texCoord;

void main()
{
    gl_Position = projection * model * vec4(aPos, 1.0);

    vec2 normalizedOffset = uvOffset / textureSize;
    vec2 normalizedScale = frameSize / textureSize;
    texCoord = (aTex * normalizedScale) + normalizedOffset;
}