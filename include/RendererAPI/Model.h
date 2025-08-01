//
// Created by Carlo Baretta on 31/07/2025.
//

#ifndef MODEL_H
#define MODEL_H
#include "cglm/struct/mat4.h"
#include "RendererAPI/Transformation.h"

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
struct Model {
    char *name;
    unsigned int id;
    unsigned int shaderProgramID;
    size_t indicesCount;
    struct Texture *textures;
    size_t textureCount;
    struct Transformation transformation;
};

#endif //MODEL_H
