#pragma once

#include <cmath>
#include <SDL.h>
#include <vector>
#include "Entity.hpp"
#include "RenderWindow.hpp"
#include <iostream>
#include "Math.hpp"
#include "Blocks.hpp"

class Generation {
public:
    Generation(RenderWindow p_window) : window(p_window) {}

    int getBlockWidth();
    int getBlockHeight();
    int getMidline();
    std::vector<SDL_Texture*> action(std::string blockName);
    std::vector<Entity> generate();


private:
    RenderWindow window;
    bool belowMidline;
    int blocksW = floor(SDL_GetWindowSurface(window.getWindow())->w / 64) + 1;
    int blocksH = floor(SDL_GetWindowSurface(window.getWindow())->h / 64) + 1;
    int midline = floor(blocksH / 2) + 1;
    SDL_Texture* grassTexture = window.loadTexture("res/png/grass.png");
    SDL_Texture* dirtTexture = window.loadTexture("res/png/dirt.png");
    SDL_Texture* grassHTexture = window.loadTexture("res/png/grass_hover.png");
    SDL_Texture* dirtHTexture = window.loadTexture("res/png/dirt_hover.png");
    SDL_Texture* voidTexture = window.loadTexture("res/png/voidblock.png");
    SDL_Texture* voidHTexture = window.loadTexture("res/png/voidblock_hover.png");
    SDL_Texture* woodTexture = window.loadTexture("res/png/wood.png");
    SDL_Texture* woodHTexture = window.loadTexture("res/png/wood_hover.png");
};