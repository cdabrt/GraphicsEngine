//
// Created by Carlo Baretta on 14-7-2025.
//


#include <stdio.h>
#include <stdlib.h>

char *readFile (char fileName[]) {
    const int offset = 0;
    const int elementSize = 1;

    FILE *sourceFile = fopen(fileName, "r");
    if (!sourceFile) {
        perror("Failed to open file");
        return NULL;
    }

    fseek(sourceFile, offset, SEEK_END);
    const long fileSize = ftell(sourceFile);
    rewind(sourceFile);

    char *sourceString = malloc(fileSize + 1);

    size_t bytesRead = fread(sourceString, elementSize, fileSize, sourceFile);
    sourceString[bytesRead] = '\0';

    fclose(sourceFile);

    return sourceString;
}
