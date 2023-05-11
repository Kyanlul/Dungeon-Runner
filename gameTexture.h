#pragma once
#include "texture.h"
#include "constants.h"

LTexture bossTexture,bossBulletTexture,tile;
LTexture pHealth;

void loadAllTexture(SDL_Renderer* renderer)
{
    //boss
    bossTexture.loadFromFile(renderer,"./assets/CosmicNose.png");
    bossBulletTexture.loadFromFile(renderer,"./assets/bossBullet.png");
    //terrain
    tile.loadFromFile(renderer,"./assets/floor_1.png");
    //hud
    pHealth.loadFromFile(renderer,"./assets/playerHealth.png");

}

