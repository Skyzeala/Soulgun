#include "TextureManager.h"

/**
 * Loads all pre-defined textures
 * 
 * @param renderer An external renderer needed to create textures
 */
TextureManager::TextureManager(SDL_Renderer *renderer) {
    externalRenderer = renderer;

    for (int id = 0; id < TX_TOTAL; ++id) {
        load(static_cast<TextureID>(id));
    }
}

/**
 * Unloads all loaded textures
 */
TextureManager::~TextureManager(void) {
    for (int id = 0; id < TX_TOTAL; ++id) {
        unload(static_cast<TextureID>(id));
    }
}

/**
 * Retrieves a texture that has been loaded
 * 
 * @param id The texture ID to retrieve
 * @returns A pointer to the texture
 */
SDL_Texture *TextureManager::getTexture(TextureID id) {
    return textures[id];
}

/**
 * Retrieves the dimensions of a texture that has been loaded
 * 
 * @param id The texture ID to retrieve dimensions for
 * @returns An SDL point struct (x = width, y = height)
 */
SDL_Point TextureManager::getDimensions(TextureID id) {
    return dimensions[id];
}

/**
 * Loads a image into memory and creates a texture from it
 * 
 * @param id The texture ID to load
 * @returns A pointer to the texture that was created, or NULL if failed
 */
SDL_Texture *TextureManager::load(TextureID id) {
    // Reload if already loaded
    if (textures[id] != NULL)
        unload(id);

    // First image must be loaded onto a surface
    const char *path = paths[id].c_str();
    SDL_Surface *surface = IMG_Load(path);

    if (!surface) {
        printf("Error loading image %s: %s", path, IMG_GetError());
        return NULL;
    }

    // Now texture can be created from surface
    SDL_Texture *texture = SDL_CreateTextureFromSurface(externalRenderer, surface);
    if (!texture)
        printf("Error creating texture from %s: %s", path, SDL_GetError());
    SDL_FreeSurface(surface);

    textures[id] = texture;
    return texture;
}

/**
 * Loads a image into memory and creates a texture from it
 * 
 * @param id The texture ID to load
 * @returns A pointer to the texture that was created, or NULL if failed
 */
void TextureManager::unload(TextureID id) {
    SDL_DestroyTexture(textures[id]);
    textures[id] = NULL;
    dimensions[id].x = 0;
    dimensions[id].y = 0;
}