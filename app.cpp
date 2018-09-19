#include "app.h"
#include <QtDebug>

App::App(QObject *parent) : QObject(parent)
{
}

/**
 * @brief App::initApp
 *
 * 初始化基本的SDL环境
 * @return
 */
bool App::initAppEnv()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        qDebug() << "SDL_Init Error: " << SDL_GetError() ;
        return false;
    }
    int flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP;
    if((IMG_Init(flags) & flags) != flags){
        qDebug() << "IMG_Init Error: " << SDL_GetError() ;
        return false;
    }
    if(TTF_Init() != 0){
        qDebug() << "TTF_Init Error: " << SDL_GetError() ;
        return false;
    }

    bool isInit = this->initPrivate();
    StartExecute();
    return isInit;
}

// 父类就是先画背景图（画背景图可以在子类中重定义），然后进行事件循环，子类可以处理事件循环
void App::execute()
{
    myRenderBackground();
    while(this->isRunning){
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            switch(e.type){
            case SDL_QUIT:
                StopExecute();
                break;
            default:
                this->onEvent(e);
            }
        }

    }
}



/**
 * @brief App::~App
 * 销毁基本的SDL环境，销毁之前你可能需要自己释放所有的resource，也就是你
 * 分配的surface等等
 */
App::~App()
{
}

// 利用SDL_TTF来加载并渲染字体到Texture上
SDL_Texture *App::renderText(const QString &strMessage, const QString &strFontFile, const SDL_Color objColor, const int iFontSize, SDL_Renderer * objRenderer)
{
    TTF_Font *objFont = TTF_OpenFont(strFontFile.toLocal8Bit().data(), iFontSize);
    if (objFont == nullptr){
        qDebug() << "TTF_OpenFont";
        return nullptr;
    }

    SDL_Surface *objSurf = TTF_RenderText_Blended(objFont, strMessage.toLocal8Bit().data(), objColor);
    if (objSurf == nullptr){
        CleanUp(objFont);
        qDebug() << "TTF_RenderText";
        return nullptr;
    }

    SDL_Texture *objTexture = SDL_CreateTextureFromSurface(objRenderer, objSurf);
    if (objTexture == nullptr){
        qDebug() <<  "CreateTexture";
    }
    CleanUp(objSurf, objFont);
    return objTexture;
}


// 利用SDL_TTF来加载并渲染字体到Texture上
SDL_Texture *App::renderImage(const QString &strFilePath, SDL_Renderer * objRenderer)
{
    return IMG_LoadTexture(objRenderer, strFilePath.toLocal8Bit().data());
}

void App::releaseAppEnv()
{
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}



void App::StartExecute()
{
    this->isRunning = true;
}

void App::StopExecute()
{
    this->isRunning = false;
}
