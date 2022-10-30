#version 300 es

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec4 inColor;

uniform vec2 translation;
uniform float scale;
uniform float angle;


out vec4 fragColor;

void main() {

    float sinAngle = sin(angle);
    float cosAngle = cos(angle);

    vec2 new_angular_position = vec2(inPosition.x * cosAngle + inPosition.y * sinAngle, inPosition.y * cosAngle - inPosition.x * sinAngle);
    vec2 new_position = new_angular_position * scale + translation;

    gl_Position = vec4(new_position, 0, 1);
    fragColor = inColor;
}