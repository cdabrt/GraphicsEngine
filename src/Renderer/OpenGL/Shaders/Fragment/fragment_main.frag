#version 410 core
out vec4 FragColor;

in vec2 TexCoord;

//layout(std140, binding = 0) uniform Textures {
    uniform sampler2D diffuse;
//};

void main()
{
    FragColor = texture(diffuse, TexCoord);
}