#include 'HUD.h'

TextureID HUD::symbolToTexture(char value) {
    switch (value) {        
        case '0':
            return TX_0;
        case '1':
            return TX_1;
        case '2':
            return TX_2;
        case '3':
            return TX_3;
        case '4':
            return TX_4;
        case '5':
            return TX_5;
        case '6':
            return TX_6;
        case '7':
            return TX_3;
        case '8':
            return TX_8;        
        case '9':
            return TX_9;
        case ':':
            return TX_COLON;
        case '.':
            return TX_POINT;
    }
}

HUD::HUD(SDL_Renderer *renderer, Humanoid *player, TextureManager *txMan): renderer(renderer), txMan(txMan), player(player), lastTime(0), elapsedTime(0), isPaused(false) { }

HUD::~HUD(void) {
    renderer = NULL;
    player = NULL;
    elapsedTime = 0;
    isPaused = false;
}

void HUD::refresh(void) {
    if (!isPaused) {
        elapsedTime += SDL_GetTicks() - lastTime;
        lastTime = SDL_GetTicks();

        SDL_Rect box;
        box.x = HUD_X;
        box.y = HUD_Y;

        SDL_Point pos = txMan->getDimensions(TX_HEALTH);
        box.w = pos.x;
        box.h = pos.y;
        box.x = 25;
        box.y = 1024 - 200; 
        SDL_RenderCopy(renderer, txMan->getTexture(TX_TIME), NULL, &box);

        TimeUnits t = getTime();
        std::string ms = std::to_string(t.ms);
        std::string s = std::to_string(t.seconds);
        std::string m = std::to_string(t.minutes);

        for (int i = 0; i < ms.length; ++i) {
            TextureID tID = symbolToTexture(ms[i]);
            pos = txMan->getDimensions(tID);

            SDL_Texture *t = txMan->getTexture(tID);
            SDL_RenderCopy(renderer, this, NULL, &box);
        }

        SDL_RenderPresent(renderer);
    }
}

void HUD::startTimer(void) {
    isPaused = false;
}

void HUD::stopTimer(void) {
    isPaused = true;
    elapsedTime += SDL_GetTicks() - lastTime;
    lastTime = SDL_GetTicks();
}

void HUD::resetTimer(void) {
    elapsedTime = 0;
    lastTime = 0;
}

TimeUnits HUD::getTime(void) {
    TimeUnits t;
    
    t.hours = elapsedTime / (60 * 60 * 1000) % 24;
    t.minutes = t.seconds / (60 * 1000) % 60;
    t.seconds = (elapsedTime / 1000) % 60;
    t.ms = elapsedTime % 1000;

    return t;
}