#include <vector>
#include "Entity.hpp"
#include "Generation.hpp"
#include "Math.hpp"
#include "Blocks.hpp"
#include <cmath>
#include <iostream>

int Generation::getBlockWidth() {
    return Generation::blocksW;
}

int Generation::getBlockHeight() {
    return Generation::blocksH;
}

int Generation::getMidline() {
    return Generation::midline;
}


std::vector<Entity> Generation::generate() {
    std::vector<Entity> entities;
    for(int i = 0; i < getBlockWidth(); i++) {
        for(int j = 0; j < getBlockHeight(); j++) {
            if(j > getMidline()) { belowMidline = true; }
            else { belowMidline = false; }

            if(belowMidline) {
                // can be both
                if(j > (getMidline() + 1)) {
                    entities.push_back(Entity(Vector2f(64*i, 64*j), dirtTexture, "dirt", dirtTexture, dirtHTexture));
                } else {
                    entities.push_back(Entity(Vector2f(64*i, 64*j), grassTexture, "grass", grassTexture, grassHTexture));
                }

            } else {
                int currentBlockChoice = round(rand() % 3);
                if(currentBlockChoice == 1) {
                    entities.push_back(Entity(Vector2f(64*i, 64*j), grassTexture, "grass", grassTexture, grassHTexture));
                } else if (currentBlockChoice == 2) {
                    entities.push_back(Entity(Vector2f(64*i, 64*j), voidTexture, "VOID", voidTexture, voidHTexture));
                } else {
                    entities.push_back(Entity(Vector2f(64*i, 64*j), voidTexture, "VOID", voidTexture, voidHTexture));
                }
            }

        }

    }
    return entities;
}

std::vector<SDL_Texture*> Generation::action(std::string blockName) {
    switch (stringToBlocks(blockName)) {
        case Blocks::DIRT:
            // Handle dirt
            return std::vector<SDL_Texture*> {dirtTexture, dirtHTexture};
            std::cout << "You clicked a dirt block";
            break;
        case Blocks::GRASS:
            // Handle grass
            return std::vector<SDL_Texture*> {grassTexture, grassHTexture};
            std::cout << "You clicked a grass block";
            break;
        case Blocks::WOOD:
            // Handle grass
            return std::vector<SDL_Texture*> {woodTexture, woodHTexture};
            std::cout << "You clicked a grass block";
            break;
        case Blocks::VOIDBLOCK:
            // Handle grass
            return std::vector<SDL_Texture*> {voidTexture, voidHTexture};
            std::cout << "You clicked a grass block";
            break;
    }
}