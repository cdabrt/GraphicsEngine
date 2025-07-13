//
// Created by Carlo Baretta on 13/07/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <glad/Glad.h>
#include "OpenGLRenderer.h"
#include <UtilFiles/ReadFile.h>
#include <string.h>



void openGLInitialize(const int xPos, const int yPos, const int width, const int height) {
    //Initialise GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        perror("Failed to initialize GLAD \n");
        exit(EXIT_FAILURE);
    }

    //Create viewport
    /*
     Note: This can be made smaller than the actual window (GLFWwindow*),
     so that you can use for example native UI elements around the smaller viewport that renders the OpenGL graphics.
    */
    glViewport(xPos, yPos, width, height);
}

void checkCompilationSuccess(unsigned int shader);
void checkLinkingSuccess(unsigned int program);



unsigned int compileShader (char fileName[], const unsigned int shaderType) {
    const unsigned int shader = glCreateShader(shaderType);
    char *shaderSource = readFile(fileName);

    //Attach shader source to the shader object and compile
    glShaderSource(shader, 1, (const GLchar * const*) &shaderSource, nullptr);
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



//Poll events and swat front buffer with back buffers
void openGLRender (void *context, float vertices[]) {
    struct OpenGLContext *openGLContext = (struct OpenGLContext *)context;
    constexpr int MAX_NAME_LENGTH = 300;
    constexpr char filePathBase[] = "../src/Renderer/OpenGL/Shaders/";
    char fullPath[strlen(filePathBase) + MAX_NAME_LENGTH + 1];

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    strcpy(fullPath, filePathBase);
    const unsigned int vertexShader = compileShader(
        strncat(fullPath, "Vertex/vertex_main.vert", sizeof(fullPath) - strlen(fullPath) - 1),
        GL_VERTEX_SHADER
        );

    strcpy(fullPath, filePathBase);
    const unsigned int fragmentShader = compileShader(
        strncat(fullPath, "Fragment/fragment_main.frag", sizeof(fullPath) - strlen(fullPath) - 1),
        GL_FRAGMENT_SHADER
        );

    const unsigned int shaderProgram = linkShaders(vertexShader, fragmentShader);

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //TODO: Temporary background colour
    glClearColor(0.4f, 0.5f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}



//Poll events and swat front buffer with back buffers
void openGLSwapBuffers (void *context) {
    struct OpenGLContext *openGLContext = (struct OpenGLContext *)context;
    glfwPollEvents();
    glfwSwapBuffers(openGLContext->window);
}



void checkCompilationSuccess(const unsigned int shader) {
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        sprintf("Shader compilation failed.\n", infoLog);
    }
}

void checkLinkingSuccess(const unsigned int program) {
    int  success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        sprintf("Program linking failed.\n", infoLog);
    }
}