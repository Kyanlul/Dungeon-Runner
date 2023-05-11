#pragma once
#include "constants.h"
#include "texture.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


std::string defaultFont = "assets/Lmao.ttf";
struct textTexture
{
    textTexture(int x,int y,int size,std::string str,std::string fontPath,SDL_Color color);
    ~textTexture();
    void render(SDL_Renderer *renderer);
    void initWH();
    int x,y;
    int size;
    int w,h;
    std::string str;
    SDL_Color color;
    TTF_Font* font;
    std::string fontPath;
    SDL_Texture* texture;
};

textTexture::textTexture(int x,int y,int size,std::string str,std::string fontPath = defaultFont,SDL_Color color = {255,255,255,255})
{
    this->x=x;
    this->y=y;
    this->size=size;
    this->str=str;
    this->fontPath=fontPath;
    this->color=color;
    this->font=TTF_OpenFont(fontPath.c_str(),size);
    this->texture=NULL;
    initWH();
}
textTexture::~textTexture()
{
    if(texture!=NULL)
        SDL_DestroyTexture(texture);
    if(font!=NULL)
        TTF_CloseFont(font);
}
void textTexture::initWH()
{
    TTF_SizeText(font,str.c_str(),&w,&h);
}
void textTexture::render(SDL_Renderer *renderer)
{
    if(font==NULL) 
    {
        std::cout<<"Font not found!"<<'\n';
        return ;
    }
    //std::cout<<"Rendering text..."<<str<<'\n';
    SDL_Surface* surface=TTF_RenderText_Solid(font,str.c_str(),color);
    texture=SDL_CreateTextureFromSurface(renderer,surface);
    SDL_Rect rect={x,y,surface->w,surface->h};
    SDL_RenderCopy(renderer,texture,NULL,&rect);
    SDL_FreeSurface(surface);
}

void drawText(SDL_Renderer *renderer, int x, int y, int size, std::string s, SDL_Color color = {255,255,255,255}, std::string font = defaultFont)// boxSize for allign
{
    textTexture t(x,y,size,s,font,color);
    t.render(renderer);
}
void drawTextCenter(SDL_Renderer *renderer, int x, int y, int size, std::string s, int boxWidth, int boxHeight, SDL_Color color = {255,255,255,255}, std::string font = defaultFont)// boxSize for allign
{
    textTexture t(x,y,size,s,font,color);
    t.x+=(boxWidth-t.w)/2;
    t.y+=(boxHeight-t.h)/2;
    t.render(renderer);
}