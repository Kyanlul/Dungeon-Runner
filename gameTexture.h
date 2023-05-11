#pragma once
#include "texture.h"
#include "constants.h"



LTexture bossTexture,bossBulletTexture,tile,rageBossBullet;
LTexture pBullet;
LTexture pHealth;

void loadAllTexture(SDL_Renderer* renderer)
{
    //boss
    bossTexture.loadFromFile(renderer,"./assets/bossmain.png");
    bossBulletTexture.loadFromFile(renderer,"./assets/bossBullet.png");
    rageBossBullet.loadFromFile(renderer, "./assets/bossBulletRage.png");
    //terrain
    tile.loadFromFile(renderer,"./assets/floor.png");
    //hud
    pHealth.loadFromFile(renderer,"./assets/heart.png");
    pBullet.loadFromFile(renderer, "./assets/Pbullet.png");

}

