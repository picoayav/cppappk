#include <SDl.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"
#include "Generation.hpp"
#include <unordered_map>
#include <cmath>
#include "Blocks.hpp"
#include "StringManipulation.hpp"
#include <fstream>
#include <algorithm>
#include "InventoryItem.hpp"
#include <cstdio>



int main(int argc, char** args) {
    if (SDL_Init(SDL_INIT_VIDEO) > 0) {
        std::cout << "SDL_Init_VIDEO failed or something lmao, SDL_ERROR: " << SDL_GetError() << std::endl;
        return -1;
    }
    if (!(IMG_Init(IMG_INIT_PNG))) {
        std::cout << "IMG_Init failed or something lmao, get better. SDL_ERROR: " << IMG_GetError() << std::endl;
        return -1;
    }


    RenderWindow window("Game v-1.0", 1080, 720);
    int windowRefreshRate = window.getRefreshRate();

    int xMouse, yMouse;

    bool isPlacing = true;

    Blocks curBlock = Blocks::DIRT;
    std::string curType = "dirt";

    SDL_Texture* blockTex;
    SDL_Texture* hBlockTex;

    switch(curBlock) {

        case Blocks::DIRT:
            blockTex = window.loadTexture("res/png/dirt.png");
            hBlockTex = window.loadTexture("res/png/dirt_hover.png");
            break;

        case Blocks::GRASS:
            blockTex =  window.loadTexture("res/png/grass.png");
            hBlockTex = window.loadTexture("res/png/grass_hover.png");
            break;
        case Blocks::VOIDBLOCK:
            blockTex =  window.loadTexture("res/png/voidblock.png");
            hBlockTex = window.loadTexture("res/png/voidblock_hover.png");
            break;
    }


    Generation generator = Generation(window);
    StringManipulation manipulator;





    std::vector<Entity> entities = generator.generate();

    std::vector<InventoryItem>(8);

    //SDL_GetWindowSurface(window.getWindow())->w (Get Window Width)


    bool gameRunning = true;

    SDL_Event event;


    const float timeStep = 0.01f;
    float accumulator = 0.0f;
    float currentTime = utils::hireTimeInSeconds();


    while(gameRunning) {
        int startTicks = SDL_GetTicks();
        float newTime = utils::hireTimeInSeconds();
        float frameTime = newTime - currentTime;
        currentTime = newTime;
        accumulator += frameTime;
        if (frameTime > 0.25f)
            frameTime = 0.25f;

        while (accumulator >= timeStep)  {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    gameRunning = false;
                }
                if (event.type == SDL_KEYUP) {
                    switch (event.key.keysym.sym) {
                        //used to refresh display
                        case SDLK_r: {
                            entities.clear();
                            entities = generator.generate();
                            break;
                        }
                        //SDLK_l and SDLK_s both are used to save.
                        case SDLK_l: {
                            std::ifstream testFile("save.txt");
                            std::string line;

                            std::vector<std::string> lines;
                            entities.clear();

                            while(getline(testFile, line)){
                                std::vector<std::string> ln = manipulator.splice(line, ',');
                                float xPos = std::stof(ln[0]);
                                float yPos = std::stof(ln[1]);
                                Vector2f v2f = Vector2f(xPos, yPos);
                                std::vector<SDL_Texture*> tex = generator.action(ln[2]);
                                entities.push_back(Entity(v2f, tex[0], ln[2], tex[0], tex[1]));


                            }
                            break;
                        }
                        case SDLK_s: {
                            std::ofstream saveFile;
                            remove("save.txt");
                            saveFile.open("save.txt", std::ios_base::app);
                            std::string finalStr;
                            for(int i = 0; i < entities.size(); i++) {
                                //{x13, y444dirt}
                                finalStr = std::to_string((int) entities[i].getPos().x) + ',' +std::to_string((int) entities[i].getPos().y) + ',' + entities[i].getType() + "\n";
                                saveFile << finalStr;
                            }
                            saveFile.close();
                            break;
                        }
                        case SDLK_t: {
                            isPlacing = !isPlacing;
                            break;
                        }
                        case SDLK_c: {
                            std::vector<Entity> newEntities;
                            for(int i = 0; i < entities.size(); i++) {
                                Entity newEntity = Entity(Vector2f(entities[i].getPos().x, entities[i].getPos().y),window.loadTexture("res/png/voidblock.png"), "VOID",window.loadTexture("res/png/voidblock.png"),window.loadTexture("res/png/voidblock_hover.png"));
                                newEntities.push_back(newEntity);
                            }
                            entities.clear();
                            entities = newEntities;

                        }
                        case SDLK_0: {
                            curBlock = Blocks::DIRT;
                            curType = "dirt";
                            switch(curBlock) {
                                case Blocks::DIRT:
                                    blockTex = window.loadTexture("res/png/dirt.png");
                                    hBlockTex = window.loadTexture("res/png/dirt_hover.png");
                                    break;
                                case Blocks::WOOD:
                                    blockTex =  window.loadTexture("res/png/wood.png");
                                    hBlockTex = window.loadTexture("res/png/wood_hover.png");
                                    break;

                                case Blocks::GRASS:
                                    blockTex =  window.loadTexture("res/png/grass.png");
                                    hBlockTex = window.loadTexture("res/png/grass_hover.png");
                                    break;
                                case Blocks::VOIDBLOCK:
                                    blockTex =  window.loadTexture("res/png/voidblock.png");
                                    hBlockTex = window.loadTexture("res/png/voidblock_hover.png");
                                    break;
                            }
                            break;
                        }
                        case SDLK_1: {
                            curBlock = Blocks::GRASS;
                            curType = "grass";
                            switch(curBlock) {

                                case Blocks::DIRT:
                                    blockTex = window.loadTexture("res/png/dirt.png");
                                    hBlockTex = window.loadTexture("res/png/dirt_hover.png");
                                    break;

                                case Blocks::GRASS:
                                    blockTex =  window.loadTexture("res/png/grass.png");
                                    hBlockTex = window.loadTexture("res/png/grass_hover.png");
                                    break;
                                case Blocks::WOOD:
                                    blockTex =  window.loadTexture("res/png/wood.png");
                                    hBlockTex = window.loadTexture("res/png/wood_hover.png");
                                    break;
                                case Blocks::VOIDBLOCK:
                                    blockTex =  window.loadTexture("res/png/voidblock.png");
                                    hBlockTex = window.loadTexture("res/png/voidblock_hover.png");
                                    break;
                            }
                            break;
                        }
                        case SDLK_2: {
                            curBlock = Blocks::WOOD;
                            curType = "wood";
                            switch(curBlock) {
                                case Blocks::DIRT:
                                    blockTex = window.loadTexture("res/png/dirt.png");
                                    hBlockTex = window.loadTexture("res/png/dirt_hover.png");
                                    break;
                                case Blocks::WOOD:
                                    blockTex =  window.loadTexture("res/png/wood.png");
                                    hBlockTex = window.loadTexture("res/png/wood_hover.png");
                                    break;

                                case Blocks::GRASS:
                                    blockTex =  window.loadTexture("res/png/grass.png");
                                    hBlockTex = window.loadTexture("res/png/grass_hover.png");
                                    break;
                                case Blocks::VOIDBLOCK:
                                    blockTex =  window.loadTexture("res/png/voidblock.png");
                                    hBlockTex = window.loadTexture("res/png/voidblock_hover.png");
                                    break;
                            }
                            break;
                        }
                    }
                }
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        SDL_GetMouseState(&xMouse, &yMouse);
                        for (int i = 0; i < entities.size(); i++) {
                            SDL_Point point = {xMouse, yMouse};
                            SDL_Rect src;
                            src.x = entities[i].getPos().x;
                            src.y = entities[i].getPos().y;
                            src.w = 64;
                            src.h = 64;
                            if(SDL_PointInRect(&point, &src) == SDL_TRUE) {
                                std::string type = entities[i].getType();

                                // Now 'blockEnumValue' will hold either Blocks::DIRT or Blocks::GRASS based on the input string.

                                // You can use a switch statement with the Blocks enum value
                                //action(type);
                                if(!isPlacing && entities[i].getType() != "VOID") {
                                    Entity newEntity = Entity(
                                            Vector2f(entities[i].getPos().x, entities[i].getPos().y),
                                                              window.loadTexture("res/png/voidblock.png"), "VOID",
                                                              window.loadTexture("res/png/voidblock.png"),
                                                              window.loadTexture("res/png/voidblock_hover.png")
                                                              );
                                    entities.push_back(newEntity);
                                    entities.erase(entities.begin() + i);
                                } else if (isPlacing) {
                                    Entity newEntity = Entity(Vector2f(entities[i].getPos().x, entities[i].getPos().y), blockTex, curType, blockTex,  hBlockTex);
                                    entities.push_back(newEntity);
                                    entities.erase(entities.begin() + i);
                                }
                            }

                        }

                    }
                }
                if (event.type == SDL_MOUSEMOTION) {
                    SDL_GetMouseState(&xMouse, &yMouse);
                    for (int i = 0; i < entities.size(); i++) {
                        {
                            SDL_Point point = {xMouse, yMouse};
                            SDL_Rect src;
                            src.x = entities[i].getPos().x;
                            src.y = entities[i].getPos().y;
                            src.w = 64;
                            src.h = 64;
                            if (SDL_PointInRect(&point, &src) == SDL_TRUE) {
                                entities[i].hover();
                            } else {
                                entities[i].unHover();
                            }
                        }
                    }

                }



            }
            accumulator -= timeStep;

        }
        const float alpha = accumulator / timeStep;

        window.clear();
        for(Entity& e : entities) {
            window.render(e);
        }
        window.display();

        int frameTicks = SDL_GetTicks() - startTicks;

        if (frameTicks < 1000 /window.getRefreshRate()) {
            SDL_Delay(1000 / window.getRefreshRate() - frameTicks);

        }
    }
    window.cleanUp();
    SDL_Quit();

    return 0;
}


