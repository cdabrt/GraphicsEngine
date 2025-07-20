//
// Created by Carlo Baretta on 14/07/2025.
//

#include <stdio.h>
#include "../include/RendererAPI/Mesh.h"
#include "Renderer/OpenGL/OpenGLErrorHandling.h"
#include "UtilFiles/ReadFile.h"
#include "Renderer/OpenGL/OpenGLContext.h"
#include "Renderer/OpenGL/OpenGLMacros.h"
#include <stb_image.h>
#include <_string.h>

#include "Renderer/OpenGL/OpenGLHeaders.h"


unsigned int compileShader (char filePath[], const unsigned int shaderType) {
    const unsigned int shader = glCreateShader(shaderType);
    const int numberOfShaders = 1;
    char *shaderSource = readFile(filePath);

    //Attach shader source to the shader object and compile
    glShaderSource(shader, numberOfShaders, (const GLchar * const*) &shaderSource, NULL);
    free(shaderSource);
    glCompileShader(shader);

    checkCompilationSuccess(shader);

    return shader;
}

unsigned int linkShaders (const unsigned int vertexShader, const unsigned int fragmentShader) {
    const unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    checkLinkingSuccess(shaderProgram);

    return shaderProgram;
}

/*
 Because we create the shader program in this function,
 this function can be exposed so external developers can add their own shaders
 */
unsigned int openGLCreateShaderProgram(char *vertexFilePath, char *fragmentFilePath) {
    const unsigned int vertexShader = compileShader(
        vertexFilePath,
        GL_VERTEX_SHADER
        );

    const unsigned int fragmentShader = compileShader(
    fragmentFilePath,
        GL_FRAGMENT_SHADER
        );

    const unsigned int shaderProgram = linkShaders(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

void openGLSetActiveShaderProgram(void *context, const unsigned long programId) {
    OPENGL_CTX;

    glUseProgram(programId);
    openGLContext->activeShaderProgram = programId;
}



void setTextureParameters() {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void generateTexture(struct Texture *texture, const GLuint textureID, const int index, const int nrChannels,
    const int width, const int height, const unsigned char *data) {
    const int border = 0;
    const int level = 0;

    GLint format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, level, GL_RGB, width, height, border,
                format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    texture->id = textureID;
    texture->textureUnit = GL_TEXTURE0 + index;
}

void registerFileNotFoundImage(struct OpenGLContext *context, struct VAO *vao) {
    const char *fileNotFoundPath = strdup("../src/Renderer/OpenGL/Textures/FileNotFound.png");
    const int numberOfRegistersAtTime = 1;
    int width, height, nrChannels;
    const int desiredChannels = 0;
    GLuint textureID;

    glGenTextures(numberOfRegistersAtTime, &textureID);
    setTextureParameters();

    unsigned char *data = stbi_load(fileNotFoundPath, &width, &height, &nrChannels, desiredChannels);
    free(fileNotFoundPath);

    struct Texture texture = {
        (char *) fileNotFoundPath,
        DIFFUSE,
        "diffuse",
        textureID,
        GL_TEXTURE0
    };

    generateTexture(&texture, textureID, 0, nrChannels, width, height, data);
    addTexture(context, vao, texture);
    stbi_image_free(data);
}

void registerTextures(struct OpenGLContext *context, const struct Texture *textures, const size_t textureCount) {
    const int numberOfRegistersAtTime = 1;
    int width, height, nrChannels;
    const int desiredChannels = 0;

    struct VAO *vao = &context->vaos[context->vaoCount - 1];

    if (textureCount == 0) {
        registerFileNotFoundImage(context, vao);
    } else {
        for (int i = 0; i < textureCount; i++) {
            struct Texture texture = textures[i];
            GLuint textureID;

            glGenTextures(numberOfRegistersAtTime, &textureID);
            setTextureParameters();

            stbi_set_flip_vertically_on_load(1);
            unsigned char *data = stbi_load(texture.path, &width, &height, &nrChannels, desiredChannels);

            if (data) {
                generateTexture(&texture, textureID, i, nrChannels, width, height, data);
                addTexture(context, vao, texture);
            }
            else {
                stbi_image_free(data);
                registerFileNotFoundImage(context, vao);
                printf("Failed to load texture: %s\n", stbi_failure_reason());
                return;
            }
            stbi_image_free(data);
        }
    }
}

//TODO: Register static mesh, put it into one big VBO and use glMultiDrawIndirect for frustum culling of the big static VBO.
//  The dynamic meshes still need to be frustum culled
//  Also look into instancing (trees, bullets, etc)
void openGLRegisterMesh(void *context, const struct Mesh *mesh) {
    OPENGL_CTX;
    const int vertexAttribIndex = 0;
    const int vertexColourAttribIndex = 1;
    const int textureCoordinatesIndex = 2;
    const int vertexBlockSize = 3;
    const int textureCoordinatesBlockSize = 2;
    const int stride = 8;

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertexDataSize, mesh->vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indicesDataSize, mesh->indices, GL_STATIC_DRAW); ;

    //Vertex position
    glVertexAttribPointer(vertexAttribIndex, vertexBlockSize, GL_FLOAT, GL_FALSE,
        stride * sizeof(float), NULL);
    glEnableVertexAttribArray(vertexAttribIndex);

    //Colour position
    glVertexAttribPointer(vertexColourAttribIndex, vertexBlockSize, GL_FLOAT, GL_FALSE,
        stride * sizeof(float), (void*)(vertexBlockSize * sizeof(float)));
    glEnableVertexAttribArray(vertexColourAttribIndex);

    //Texture coordinates position
    glVertexAttribPointer(textureCoordinatesIndex, textureCoordinatesBlockSize, GL_FLOAT, GL_FALSE,
        stride * sizeof(float), (void*)(vertexBlockSize * textureCoordinatesBlockSize * sizeof(float)));
    glEnableVertexAttribArray(textureCoordinatesIndex);

    addVAO(openGLContext, VAO, mesh->indicesDataSize);
    registerTextures(openGLContext, mesh->textures, mesh->textureCount);
}