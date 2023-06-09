#pragma once
#include "constants.h"
#include <math.h>
#include "texture.h"
#include "gameTexture.h"
#include "terrain.h"
#include "move_and_collision.h"


struct bullet
{
    int x,y;
    double velX,velY;
    bool active;
    bool fromPlayer;
    bool willHit;
    int size;

    bullet() {active = 0;};
    void init(int x,int y,double velX,double velY,bool fromPlayer);
    void move();
}bulletList[maxBulletNumber];

int phase;//0: norm, 1: 50% hp, 2: 25% hp
int phaseUpdated = 0;

void bullet::init(int x,int y,double velX,double velY,bool fromPlayer = 1)
{
    this->x=x;
    this->y=y;
    this->velX=velX;
    this->velY=velY;
    this->fromPlayer = fromPlayer;
    willHit = 0;
    active=true;
    if(fromPlayer) size = 10;
    else size = 30;
}
void bullet::move()
{
    if(willHit)
    {
        active=false;
        return;
    }
    //check hit and move
    bool hitWall=0,hitEnemy=0;
    nextPos(x,y,velX,velY,size,hitWall,hitEnemy);
    if(x < 0 || x > SCREEN_WIDTH || y < 0 || y > SCREEN_HEIGHT) 
    {
        active = 0;
        return ;
    }
    hitEnemy = checkBulletHitEntity(x,y,!fromPlayer,size);
    willHit = hitWall || hitEnemy;
}
void calculateBulletVelocity(int x,int y,int px,int py,double &vx,double &vy,int vel = bVel)
{
    double tan=7777;
    if(px != x) 
    {
        tan = (double)(py-y)*1.0/(px-x);
        vx = sqrt(vel*vel / (1 + tan*tan));
        vy = sqrt(vel*vel - vx*vx);
    }
    else
    {
        vx = 0;
        vy = vel;
    }
    if(px < x) vx=-vx;
    if(py < y) vy=-vy; 
}
void addBullet(int x,int y,double velX,double velY,bool fromPlayer = 1)
{
    for(int i=0;i<maxBulletNumber;i++)
    {
        if(!bulletList[i].active)
        {
            bulletList[i].init(x,y,velX,velY,fromPlayer);
            return;
        }
    }
}
void moveBullets()
{
    for(int i=0;i<maxBulletNumber;i++)
        if(bulletList[i].active)
            bulletList[i].move();
}

void renderBullets(SDL_Renderer* renderer)
{
    for(int i=0;i<maxBulletNumber;i++)
        if(bulletList[i].active)
        {
            // //white : player, red : enemy
            // if(bulletList[i].fromPlayer)
            //     SDL_SetRenderDrawColor(renderer,255,255,255,255);
            // else
            //     SDL_SetRenderDrawColor(renderer,255,0,0,255);
            // SDL_RenderFillRect(renderer,new SDL_Rect({bulletList[i].x,bulletList[i].y,bulletList[i].size,bulletList[i].size}));
            if(bulletList[i].fromPlayer)
            {
                pBullet.render(renderer, NULL, bulletList[i].x, bulletList[i].y, bulletList[i].size, bulletList[i].size);
            }
            else
            {
                if (phase == 1 || phase == 0) bossBulletTexture.render(renderer, NULL, bulletList[i].x, bulletList[i].y, bulletList[i].size, bulletList[i].size);
                else if (phase == 2) rageBossBullet.render(renderer, NULL, bulletList[i].x, bulletList[i].y, bulletList[i].size, bulletList[i].size);
            }
        }   
}