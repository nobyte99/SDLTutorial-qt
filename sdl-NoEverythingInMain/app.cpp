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
bool App::initApp()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
            qDebug() << "SDL_Init Error: " << SDL_GetError() ;
            return false;
        }

    return this->initPrivate();
}

/**
 * @brief App::releaseResources
 * 分配自己的资源
 * @return
 */
bool App::initPrivate()
{
    return true;
}

/**
 * @brief App::releaseResources
 * 释放自己分配的资源
 * @return
 */
void App::releaseResources()
{
}

/**
 * @brief App::~App
 * 销毁基本的SDL环境，销毁之前你可能需要自己释放所有的resource，也就是你
 * 分配的surface等等
 */
App::~App()
{
    this->releaseResources();
    SDL_Quit();
}
