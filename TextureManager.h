/**
 * Texture Manager for Soulgun
 */

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

enum TextureID
{
    TX_TERRAIN,
		TX_WALL,
		TX_PIT,
    TX_PLAYER,
    TX_ROBOT,
    TX_HUMAN,
    TX_BULLET,
    TX_TOTAL
};

/**
 * Manages textures in memory
 *
 * A pre-defined set of textures can be loaded, unloaded,
 * and retrieved with its dimension meta data
 */
class TextureManager
{
public:
    TextureManager(SDL_Renderer *renderer);
    ~TextureManager(void);

    SDL_Texture *getTexture(TextureID id);
    SDL_Point getDimensions(TextureID id);

private:
    const std::string paths[TX_TOTAL] = {
        "assets/images/placeholder-terrain.png",
        "assets/images/placeholder-wall.png",
        "assets/images/placeholder-pit.png",
        "assets/images/placeholder-player.png",
        "assets/images/placeholder-robot.png",
        "assets/images/placeholder-human.png",
        "assets/images/placeholder-bullet.png"
    };

    SDL_Texture *textures[TX_TOTAL];
    SDL_Point dimensions[TX_TOTAL];
    SDL_Renderer *externalRenderer;

    SDL_Texture *load(TextureID id);
    void unload(TextureID id);
};
