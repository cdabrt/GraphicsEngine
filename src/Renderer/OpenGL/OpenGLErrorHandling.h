//
// Created by Carlo Baretta on 14/07/2025.
//

#ifndef OPENGLERRORHANDLING_H
#define OPENGLERRORHANDLING_H

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

#endif //OPENGLERRORHANDLING_H
