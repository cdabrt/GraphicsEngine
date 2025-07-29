//
// Created by Carlo Baretta on 14/07/2025.
//

#ifndef OPENGLERRORHANDLING_H
#define OPENGLERRORHANDLING_H

/**
 * checkOpenGLError
 * Checks whether any openGL error was thrown.
 */
void checkOpenGLError();


/**
 * checkCompilationSuccess
 * Checks whether compilation of the shaders was a success.
 *
 * @param shader the id of the shader.
 */
void checkCompilationSuccess(unsigned int shader);

/**
 * checkLinkingSuccess
 * Checks whether compilation of the shaders was a success.
 *
 * @param program the id of the program.
 */
void checkLinkingSuccess(unsigned int program);

/**
 * checkUniformLocation
 * Checks whether the provided uniform location exists.
 *
 * @param uniformLocation the uniform location.
 */
void checkUniformLocation(GLuint uniformLocation);

#endif //OPENGLERRORHANDLING_H
