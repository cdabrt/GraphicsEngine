//
// Created by Carlo Baretta on 14-7-2025.
//


#include <stdio.h>
#include <stdlib.h>

char *readFile (char fileName[]) {
    FILE *sourceFile = fopen(fileName, "r");
    if (!sourceFile) {
        perror("Failed to open file");
        fclose(sourceFile);
        return nullptr;
    }

    fseek(sourceFile, 0, SEEK_END);
    const long fileSize = ftell(sourceFile);
    rewind(sourceFile);

    char *sourceString = malloc(fileSize + 1);

    size_t bytesRead = fread(sourceString, 1, fileSize, sourceFile);
    sourceString[bytesRead] = '\0'; // Null terminate

    fclose(sourceFile);

    return sourceString;
}
