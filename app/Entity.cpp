#include "Entity.hpp"
#include <SDL.h>
#include <SDL_image.h>


Entity::Entity(Vector2f p_pos, SDL_Texture *p_tex, std::string p_type, SDL_Texture* p_normalTex, SDL_Texture* p_hoverTex) : pos(p_pos), tex(p_tex), type(p_type), hoverTex(p_hoverTex), normalTex(p_normalTex){
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 64;
    currentFrame.h = 64;
}

void Entity::setTexture(SDL_Texture *texture) {
    tex = texture;
}

SDL_Texture *Entity::getTexture() {
    return tex;
}

std::string Entity::getType() {
    return type;
}

SDL_Rect Entity::getCurrentFrame() {
    return currentFrame;
}

void Entity::hover() {
    setTexture(hoverTex);
}

void Entity::unHover() {
    setTexture(normalTex);
}