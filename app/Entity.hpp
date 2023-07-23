#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Math.hpp"
class Entity {
public:
    Entity(Vector2f p_pos, SDL_Texture* p_tex, std::string p_type, SDL_Texture* p_normalTex, SDL_Texture* p_hoverTex);
    Vector2f& getPos() {
        return pos;
    }
    SDL_Texture* getTexture();
    void setTexture(SDL_Texture* texture);
    std::string getType();
    SDL_Rect getCurrentFrame();
    void hover();
    void unHover();
private:
    Vector2f pos;
    SDL_Rect currentFrame;
    std::string type;
    SDL_Texture* tex;
    SDL_Texture* normalTex;
    SDL_Texture* hoverTex;

};