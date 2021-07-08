#include "TextureManager.h"

TextureManager::TextureManager(SDL_Renderer *renderer) {
    externalRenderer = renderer;

    for (int id = 0; id < TX_TOTAL; ++id) {
        load(static_cast<TextureID>(id));
    }
}

TextureManager::~TextureManager(void) {
    for (int id = 0; id < TX_TOTAL; ++id) {
        unload(static_cast<TextureID>(id));
    }
}

SDL_Texture *TextureManager::getTexture(TextureID id) {
    return textures[id];
}

SDL_Point TextureManager::getDimensions(TextureID id) {
    return dimensions[id];
}

SDL_Texture *TextureManager::load(TextureID id) {
    const char *path = paths[id].c_str();
    SDL_Surface *surface = IMG_Load(path);

    if (!surface) {
        printf("Error loading image %s: %s", path, IMG_GetError());
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(externalRenderer, surface);
    if (!texture)
        printf("Error creating texture from %s: %s", path, SDL_GetError());

    return texture;
}

void TextureManager::unload(TextureID id) {
    SDL_DestroyTexture(textures[id]);
}