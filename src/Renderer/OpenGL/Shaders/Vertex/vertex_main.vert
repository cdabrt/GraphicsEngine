#version 410 core
//As defined in the VAO
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 transform;

layout(std140) uniform CameraView {
    mat4 view;
    mat4 projection;
};

void main()
{
    /*
        Right hand coordinate system. So no need to invert the view.
        For instance, -1.0f on the z-axis will move the scene forward by 1.0f
    */
    gl_Position = projection * view * transform * vec4(aPos, 1.0f);
    TexCoord = aTexCoord;
}