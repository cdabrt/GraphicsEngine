//
// Created by Carlo Baretta on 14/07/2025.
//


#include <stdio.h>
#include "glad/Glad.h"

void checkCompilationSuccess(const unsigned int shader) {
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        perror(infoLog);
    }
}

void checkLinkingSuccess(const unsigned int program) {
    int  success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        snprintf("Program linking failed.\n", sizeof(infoLog), infoLog);
        perror(infoLog);
    }
}