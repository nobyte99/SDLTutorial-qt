#include "myshowimagettf.h"
#include <QFile>
#include <QtDebug>

myShowImageTTF::myShowImageTTF()
{
    this->objSDLRen = nullptr;
    this->objSDLTexBackground = nullptr;
    this->objSDlWin = nullptr;
    x = 0;
    y = 0;
}


// 初始化背景图，并且初始化运行环境
bool myShowImageTTF::initMyShowImageTTF(const QString &strBackgroundFile, const QString &strFontFile, const SDL_Color objColor)
{
    if(!this->initAppEnv()){  // 初始化父类
        return false;
    }

    if(!QFile::exists(strBackgroundFile) || !QFile::exists(strFontFile)){
        qDebug() << "file no exists";
        return false;
    }


    // 加载字体图
    this->objSDLTexBackground = this->renderImage(strBackgroundFile, this->objSDLRen);
    Q_ASSERT(this->objSDLTexBackground != nullptr);
    this->objSDLTexForeground = this->renderText("This is a Test!",strFontFile, objColor, 88,this->objSDLRen);
    Q_ASSERT(this->objSDLTexForeground != nullptr);

}

// 画一次背景图
void myShowImageTTF::myRenderBackground()
{
    SDL_RenderClear(this->objSDLRen);  // clear render
    SDL_RenderCopy(this->objSDLRen, this->objSDLTexBackground, NULL, NULL);
    int bW, bH;
    SDL_QueryTexture(objSDLTexForeground, NULL, NULL, &bW, &bH);
    SDL_Rect objRect;
    objRect.x = x;
    objRect.y = y;
    objRect.w = bW;
    objRect.h = bH;
    SDL_RenderCopy(this->objSDLRen, this->objSDLTexForeground, NULL, &objRect);

    //Update the screen
    SDL_RenderPresent(objSDLRen);
}
// 响应事件，进行字体位置绘制
void myShowImageTTF::onEvent(SDL_Event &e)
{

    switch(e.type){
    case SDL_KEYDOWN:
        switch (e.key.keysym.sym){
        case SDLK_LEFT:
            x = std::max(0,std::min(x, x-10));
            break;
        case SDLK_RIGHT:
            x = std::min(this->iScreenWidth,std::max(x, x+10));
            break;
        case SDLK_UP:
            y = std::max(0,std::min(y, y-10));
            break;
        case SDLK_DOWN:
            y = std::min(this->iScreenHeight,std::max(y, y+10));
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    this->myRenderBackground();
}



bool myShowImageTTF::initPrivate()
{
    iScreenWidth = 640;
    iScreenHeight = 480;
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

/**
 * @brief LoadImageOnce::releaseResources
 * 释放所有的资源
 */
void myShowImageTTF::releaseResources()
{
    CleanUp(this->objSDlWin, this->objSDLRen, this->objSDLTexBackground, objSDLTexForeground);
    qDebug() << "myShowImageTTF releaseResources()";
    this->releaseAppEnv();
}

myShowImageTTF::~myShowImageTTF()
{
    this->releaseResources();
}
