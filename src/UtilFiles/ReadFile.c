//
// Created by Carlo Baretta on 14-7-2025.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GeneralErrorHandling.h"

char *readFile (char filePath[]) {
    const int offset = 0;
    const int elementSize = 1;

    FILE *sourceFile = fopen(filePath, "r");
    if (!sourceFile) {
        perror("Failed to open file");
        return NULL;
    }

    fseek(sourceFile, offset, SEEK_END);
    const long fileSize = ftell(sourceFile);
    rewind(sourceFile);

    char *sourceString = malloc(fileSize + 1);
    checkMalloc(sourceString);


    const size_t bytesRead = fread(sourceString, elementSize, fileSize, sourceFile);
    sourceString[bytesRead] = '\0';

    fclose(sourceFile);

    if (strcmp(sourceString, "") == 0 || bytesRead == 0) {
        fprintf(stderr, "Failed to read file: %s\n", filePath);
        exit(EXIT_FAILURE);
    }

    return sourceString;
}
