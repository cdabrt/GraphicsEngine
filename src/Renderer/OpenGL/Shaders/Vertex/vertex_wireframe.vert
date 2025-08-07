#version 410 core
//As defined in the VAO
layout (location = 0) in vec3 aPos;

uniform mat4 transform;

layout(std140) uniform CameraView {
    mat4 view;
    mat4 projection;
};

void main()
{
    gl_Position = projection * view * transform * vec4(aPos, 1.0f);
}