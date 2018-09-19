#include "loadimageonce.h"
#include <QtDebug>
#include <cleanup.h>

LoadImageOnce::LoadImageOnce()
{
    this->objSDLRen = nullptr;
    this->objSDLTexBackground = nullptr;
    this->objSDlWin = nullptr;
    x = 0;
    y = 0;
}

/**
 * @brief LoadImageOnce::initLoadImageOnce
 * 进行本类初始化，首先调用父类初始化；
 * 本类初始化主要针对必须的传参进行初始化；
 *
 * @param strFilePath
 * @return
 */
bool LoadImageOnce::initLoadImageOnce(QString strFilePath,QString strFilePath2)
{
    if(!this->initAppEnv()) // 先调用父类init
        return false;

    // 进行本地特殊初始化
    this->iDelay = 2000;
    // background
    SDL_Surface *bmp=SDL_LoadBMP(strFilePath.toLocal8Bit().data());
    Q_ASSERT(bmp!=nullptr);
    this->objSDLTexBackground=SDL_CreateTextureFromSurface(this->objSDLRen,bmp);
    Q_ASSERT(objSDLTexBackground!=nullptr);
    CleanUp(bmp);
    Q_ASSERT(bmp==nullptr);

    // foreground
    SDL_Surface *bmp1=SDL_LoadBMP(strFilePath2.toLocal8Bit().data());
    Q_ASSERT(bmp1!=nullptr);
    this->objSDLTexForeground=SDL_CreateTextureFromSurface(this->objSDLRen,bmp1);
    Q_ASSERT(objSDLTexForeground!=nullptr);
    CleanUp(bmp1);
    Q_ASSERT(bmp1==nullptr);

    return true;
}

bool LoadImageOnce::initPrivate()
{
    iScreenWidth = 640;
    this->iScreenHeight = 480;
    this->objSDlWin = SDL_CreateWindow("Hello World!", 100, 100, this->iScreenWidth, iScreenHeight, SDL_WINDOW_SHOWN);
    if (objSDlWin == nullptr){
        qDebug() << "SDL_CreateWindow Error: " << SDL_GetError();
        return false;
    }
    this->objSDLRen = SDL_CreateRenderer(objSDlWin, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (objSDLRen == nullptr){
        qDebug() << "SDL_CreateRenderer Error: " << SDL_GetError();
        return false;
    }
    return true;
}

// 进行图形的绘制
void LoadImageOnce::myRenderImage(int x, int y)
{
    SDL_RenderClear(this->objSDLRen);
    //Draw the texture
    SDL_RenderCopy(this->objSDLRen, this->objSDLTexBackground, NULL, NULL);
    int bW, bH;
    SDL_QueryTexture(objSDLTexForeground, NULL, NULL, &bW, &bH);
//    int x = (this->iScreenWidth - bW)/2;
//    int y = (this->iScreenHeight - bH)/2;
    SDL_Rect objRect;
    objRect.x = x;
    objRect.y = y;
    objRect.w = bW;
    objRect.h = bH;
    SDL_RenderCopy(this->objSDLRen, this->objSDLTexForeground, NULL, &objRect);

    //Update the screen
    SDL_RenderPresent(objSDLRen);
}

void LoadImageOnce::onEvent(SDL_Event &e)
{

}

void LoadImageOnce::execute()
{
    this->x = 0;
    this->y = 0;

    App::execute();
}

void LoadImageOnce::myRenderBackground()
{
    this->myRenderImage(this->x, this->y);
}

/**
 * @brief LoadImageOnce::releaseResources
 * 释放所有的资源
 */
void LoadImageOnce::releaseResources()
{
    CleanUp(this->objSDlWin, this->objSDLRen, this->objSDLTexBackground);

}
