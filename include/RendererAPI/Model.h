//
// Created by Carlo Baretta on 31/07/2025.
//

#ifndef MODEL_H
#define MODEL_H
#include "Texture.h"
#include "RendererAPI/Transformation.h"


typedef enum MeshUniform {
    TRANSFORM,
    PROJECTION,
    VIEW
} MeshUniform;

inline char *getBaseMeshUniformString(const MeshUniform meshUniform)
{
    char *string = "\0";

    switch(meshUniform) {
        case TRANSFORM: string="transform"; break;
        case PROJECTION: string="projection"; break;
        case VIEW: string="view"; break;
        default:
            perror("Unknown mesh uniform");
    }

    return string;
}

/**
 * Model
 * Struct representing a Model, which is a processed RawMesh.
 *
 * @param id the id of the model.
 * @param indicesCount the amount of indices of all the meshes that belong to the model.
 * @param shaderProgramID it is possible for no shaderProgramID to be defined.
 * @param textures the list of textures.
 * @param textureCount the amount of textures in the list of textures.
 * @param localTransformation the local-space model transformation.
 * @param worldTransformation the world-space model transformation.
 *
 * @note In further abstractions on top of this graphics engine: For instance in a game engine, this struct can be seen as
 * the "GameObject". Your GameObject in this case will most likely also contain transformation data.
 * This information can be passed to the model struct for it to be rendered.
 */
typedef struct Model {
    char *name;
    unsigned int id;
    unsigned int shaderProgramID;
    size_t indicesCount;
    Texture *textures;
    size_t textureCount;
    Transformation transformation;
} Model;

#endif //MODEL_H
